console.log('start test fbx converter !!');
var fbxconverter = require('../bin/fbxconverter');

console.log('converter .' + fbxconverter);

fbxconverter.convert('fbx_sample.fbx', 'fbx_sample1.tidae', function(data) {
  console.log(data);
});

console.log('attention end..');