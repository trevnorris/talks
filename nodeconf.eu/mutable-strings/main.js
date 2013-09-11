var mut = require('./build/Release/mutable_strings');
var timer = require('../tools/test-script');
var afterFill = mut.afterFill;

var long_string = new Buffer(1024 * 1024).fill('a').toString('binary');

console.log(long_string.substr(0, 10));

afterFill(long_string, 'b');

console.log(long_string.substr(0, 10));
