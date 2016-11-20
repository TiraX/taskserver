var router = express.Router();
var fbxconverter = require('../bin/fbxconverter');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

// convert model function
router.post('/cm', function(req, res) {
  console.log('cm fileid = ' + req.body.fileid);
  console.log('cm filename = ' + req.body.filename);
  
  fbxconverter.convert('./public/fbx_sample.fbx', './public/fbx_sample1.tidae', function(data) {
    console.log(data);
  });
  
  var test_json = {status: 'ok..'};
  res.send(test_json);
});

module.exports = router;
