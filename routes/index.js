var express = require('express');
var request = require('request');
var fs = require('fs');
var router = express.Router();
var Task = require('../task');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

// convert model function
router.post('/process', function(req, res) {
  var fid = req.body.fileid;
  var fname = req.body.filename;
  console.log('cm fileid = ' + fid);
  console.log('cm filename = ' + fname);
  
  var task = new Task(fid);
  
  // save remote file to local
  var temp_path = 'public/tmpfiles/';
  var src_url = 'http://127.0.0.1:3000/files/' + fid + '/' + fname;
  console.log('src url is : ' + src_url);
  fs.mkdirSync(temp_path + fid);
  var dst_path = temp_path + fid + '/' + fname;
  var dl_stream = request(src_url).pipe(fs.createWriteStream(dst_path));
  console.log('file downloaded to : ' + dst_path);
  
  dl_stream.on('finish', function() {
    console.log('download finished.');
	var ext = Task.get_ext_name(fname);
	
    var src_file = './public/tmpfiles/' + fid + '/' + fname;
	
	if (ext == 'fbx') {
      task.process_models(function() {});
	}
	else if (ext == 'zip') {
      task.unzip_files(src_file, function() {
        console.log("unzip finished.");
        setTimeout(function() {
          task.process_models(function(){});
        }, 100);
        setTimeout(function() {
          task.process_textures(function(){});
        }, 110);
	  });
	}
  });
});

// remove temp directory
router.post('/remove_temp', function(req, res) {
  var fid = req.body.fileid;
  console.log('remove_temp fileid = ' + fid);
  
  // remove this directory
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
  deleteFolderRecursive('public/tmpfiles/' + fid);
  
  var test_json = {status: 'ok'};
  res.send(test_json);
});
module.exports = router;
