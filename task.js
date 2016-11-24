var request = require('request');
var unzip = require('unzip');
var fs = require('fs');
var fbxconverter = require('./bin/fbxconverter');
//var gm = require('gm');

function Task(task_id) {
  this._id = task_id;
};

Task.get_ext_name = function (path) {
  /*
  var re = /(\\+)/g; 
  var filename = path.replace(re,"#");
  var one = filename.split("#");
  var two = one[one.length-1];
  var three = two.split(".");
  var last = three[three.length-1];
  return last;
  */
  var name = path.split('.');
  var ext = name[name.length - 1];
  return ext;
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

// unzip all files to temp directory '_id'
Task.prototype.unzip_files = function (filepath, on_unzip_finish) {
  var dst_path = './public/tmpfiles/' + this._id + '/';
  var stream = fs.createReadStream(filepath).pipe(unzip.Extract({ path: dst_path }));
  stream.on('finish', on_unzip_finish);
};

// search all model files in temp directory and convert them to tidae
Task.prototype.process_models = function(on_finish) {
  var dst_path = './public/tmpfiles/' + this._id;
  var models = Task.get_files(dst_path, ['fbx']);
  var dst_path = './public/tmpfiles/' + this._id + '/';
  for (var m in models) {
    var fname = models[m];
    console.log('===== find model : ' + fname);

    var src_file = dst_path + fname;
    var dst_name = fname.replace('.fbx', '.tidae');
    var dst_file = dst_path + dst_name;
    // convert fbx model to tidae
    var convert_error = undefined;
    fbxconverter.convert(src_file, dst_file, function(data) {
      console.log('convert finished. ' + data);
	  if (data != 'success') {
        convert_error = data;
	  }
    });
    /*
	console.log('convert finished.');
	if (convert_error == undefined) {
      // send convert result back
      var info = {
        fileid: fid,
	    filename: dst_name
      };
      request.post({url:'http://127.0.0.1:3000/rm', form: info}, function(error, res, body) 
        console.log('rm request returned [%d]. error = %s.', res.statusCode, error);
        if (!error && res.statusCode == 200) {
          console.log('body: ' + body);
        }
      });
    }
	
    var test_json = {status: convert_error == undefined ? 'ok' : convert_error};
    res.send(test_json);
    */
  }
};

// search all images in temp directory and resize them
Task.prototype.process_textures = function(on_finish) {
  var dst_path = './public/tmpfiles/' + this._id;
  var textures = Task.get_files(dst_path, ['png', 'jpg']);
  console.log('textures = [%d].' , textures.length )
  for (var t in textures) {
    var tex = textures[t];
    console.log('===== find texture : ' + tex);
  }
};

module.exports = Task;