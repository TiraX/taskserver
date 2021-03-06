var config = require('./config');
var request = require('request');
var unzip = require('unzip');
var zlib = require('zlib');
var fs = require('fs');
var fbxconverter = require('./bin/fbxconverter');
var gm = require('gm');

function Task(task_id) {
  this._id = task_id;
  this._queue = [];
  this._result = [];
  this._model = "";
};

Task.get_ext_name = function (path) {
  var name = path.split('.');
  var ext = name[name.length - 1];
  return ext.toLowerCase();
}
  
// get file by ext name
Task.get_files = function (dst_path, ext) {
  var files = [];
  var search_path = function(path) {
    if (fs.existsSync(path)) {
      fs.readdirSync(path).forEach(function(file, index) {
        var cur_path = path + '/' + file;
	    if (fs.lstatSync(cur_path).isDirectory()) {
          search_path(cur_path);
	    } else {
          var ext_name = Task.get_ext_name(file);
		  if (ext.indexOf(ext_name) >= 0) {
            files.push(file);
		  }
		}
	  });
    }
  }

  search_path(dst_path);
  return files;
}

// default finish method
Task.prototype.on_finish = function() {
  var info = {
    fileid: this._id,
    filename: null
  };
  var dst_url = config.client + 'receive_file';
  var task = this;
  var sent = 0;

  var deleteFolderRecursive = function(path) {
    if( fs.existsSync(path) ) {
      fs.readdirSync(path).forEach(function(file,index){
        var curPath = path + "/" + file;
        if(fs.lstatSync(curPath).isDirectory()) { // recurse
          deleteFolderRecursive(curPath);
        } else { // delete file
          fs.unlinkSync(curPath);
        }
      });
      fs.rmdirSync(path);
    }
  };

  console.log('finished : ' + this._result);
  for (var f in this._result) {
    info.filename = this._result[f];
    request.post({url: dst_url, form: info}, function(error, res, body) {
      console.log('receive_file request returned [%d]. error = %s.', res.statusCode, error);
      if (res.statusCode == 200) {
        var ret = JSON.parse(body);
        if (ret.status == 'ok') {
          sent ++;
          if (sent >= task._result.length) {
            // all files transfered. remove tmp dir
            console.log('process done, remove tmp directory. ' + task._id);
            deleteFolderRecursive('public/tmpfiles/' + task._id);

            // notify main server this task finished
            var result = {};
            result.id = task._id;
            result.status = 0;
            result.model = task._model;
            var url = config.client + 'task_finished';
            request.post({url: url, form: result}, function(err, res, body) {
              console.log('notify task finished. ' + task._id);
            });
          }
        }
      }
    });
  }
}

// check if task is finished
Task.prototype.notify_task = function (name) {
  this._queue.pop();
  if (this._queue.length == 0) {
    this.on_finish();
  }
};

// add processed files to result[]
Task.prototype.add_result = function(names) {
  for (var f in names) {
    var n = names[f];
    this._result.push(n);
  }
};
Task.prototype.add_model_result = function(name) {
  this._result.push(name);
  this._model = name;
};

// unzip all files to temp directory '_id'
Task.prototype.process_zip_archive = function (filepath) {
  var dst_path = config.tmpDir + this._id + '/';
  var stream = fs.createReadStream(filepath).pipe(unzip.Extract({ path: dst_path }));
  var task = this;
  var dst_path = config.tmpDir + this._id;
  stream.on('finish', function() {
    // delay 100ms to make sure file stream is done.
    setTimeout(function() {
      task._queue = Task.get_files(dst_path, ['fbx', 'jpg', 'png']);
      task._result = [];
      task.process_models();
      task.process_textures();
    }, 100);
  });
};

// search all model files in temp directory and convert them to tidae
Task.prototype.process_models = function() {
  var dst_path = config.tmpDir + this._id;
  var models = Task.get_files(dst_path, ['fbx']);
  var dst_path = config.tmpDir + this._id + '/';

  var _ref = this;

  if (models.length == 0)
    return;

  //for (var m in models) {
  {
    var fname = models[0];
    var fname_lower = fname.toLowerCase();
    console.log('= find model : ' + fname);

	// rename file to lower case
	fs.renameSync(dst_path + fname, dst_path + fname_lower);

    var src_file = dst_path + fname_lower;
    var name_dae = fname_lower.replace('.fbx', '.tidae');	
    var dst_file = dst_path + name_dae;
    console.log('= convert fbx dst_file : ' + dst_file);
    // convert fbx model to tidae, sychronize
    var convert_error = undefined;
    fbxconverter.convert(src_file, dst_file, function(data) {
      console.log('convert finished. ' + data);
	  if (data != 'success') {
        convert_error = data;
	  }
    });
    
    // gzip it
    var name_gz = name_dae + '.gz';
    var dst_gz_file = dst_path + name_gz;
    console.log('= gzip tidae dst_file : ' + dst_gz_file);
    var input = fs.createReadStream(dst_file);
    var output = fs.createWriteStream(dst_gz_file);
    var gz_stream = input.pipe(zlib.createGzip()).pipe(output);

    gz_stream.on('finish', function() {
      console.log('gzip finished.' + dst_gz_file);
      _ref.add_model_result(name_gz);
      _ref.notify_task(fname);
    });
  }
};

// search all images in temp directory and resize them
Task.prototype.process_textures = function() {
  var dst_path = config.tmpDir + this._id;
  var textures = Task.get_files(dst_path, ['png', 'jpg']);
  var imageMagick = gm.subClass({imageMagick : true});
  const thumb_size = 64;
  var task = this;
  var dst_path = config.tmpDir + this._id + '/';

  for (var t in textures) {
    var name = textures[t];
    console.log('= find texture : ' + name);

    var resize_image = function(fname) {
      var fname_lower = fname.toLowerCase();
      // rename file to lower case
      fs.renameSync(dst_path + fname, dst_path + fname_lower);

      var src_file = dst_path + fname_lower;
      var name_thumb = fname_lower.replace('.png', '_thumb.png');	
      name_thumb = name_thumb.replace('.jpg', '_thumb.jpg');	
      var dst_file = dst_path + name_thumb;
      console.log('= dst_file : ' + dst_file);
      imageMagick(src_file).resize(thumb_size, thumb_size).write(dst_file, function(err) {
        console.log('resize [%s] to [%s].', src_file, dst_file);
        task.add_result([fname, name_thumb]);
        task.notify_task(fname);
      });
    }
    resize_image(name);
  }
};

module.exports = Task;