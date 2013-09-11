var ivsn = require('./build/Release/index_vs_named');
var timer = require('../tools/test-script');
var accessNamed = ivsn.accessNamed;
var accessIndexed = ivsn.accessIndexed;
var iter = 1e6;


timer('accessNamed', function() {
  var obj = { length: 10, type: 'string', used: true };
  accessNamed(obj, iter);
}, iter);


timer('accessIndexed', function() {
  var obj = { 0: 10, 1: 'string', 2: true };
  accessIndexed(obj, iter);
}, iter);
