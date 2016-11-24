console.log('start test image resize !!');
var gm = require('gm');
var im = gm.subClass({imageMagick : true});

var date = new Date();
var time = date.getTime();
im('image.png').resize(64, 64).write('image_resize.png', function(err) {
  console.log('resize done. erro = ' + err);
  console.log('time = %d.', date.getTime() - time);
});

console.log('test end..');