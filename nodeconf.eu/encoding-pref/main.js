var timer = require('../tools/test-script');
var SlowBuffer = require('buffer').SlowBuffer;
var iter = 1e7;
var sizes = [16, 1024, 1024 * 32, 1024 * 128, 1024 * 512];
var types = ['binary', 'ucs2', 'ascii', 'utf8'];


(function queueTest() {
  var size = sizes.shift();
  // Also try this with a two  character
  var buf = new SlowBuffer(size).fill('a');
  var liter = size < 1024 ? iter : (iter / size * 1024) >>> 0;

  types.forEach(function(type) {
    timer(type + ':' + size, function() {
      for (var i = 0; i < liter; i++) {
        buf.toString(type);
      }
    }, liter);
  });

  if (sizes.length > 0)
    queueTest();
}());
