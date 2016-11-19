var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

// convert model function
router.post('/cm', function(req, res) {
  console.log('cm fileid = ' + req.body.fileid);
  console.log('cm filename = ' + req.body.filename);
  
  var test_json = {status: 'ok..'};
  res.send(test_json);
});

module.exports = router;
