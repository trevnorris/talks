var timer = require('../tools/test-script');
//var limit = 0xFBEE9;
var limit = (1024 * 1024) - (1024 * 128);
var iter = 3e3;

var real_string = 'a';
for (var i = 0; i < limit; i++)
  real_string += 'a';
/* */


var jump = 1024 * 4;
var max = 50;

var str = 'a';
for (var i = 0; i < limit; i++)
  str += 'a';

function runIt() {
  process.stdout.write('' + str.length + ' ');
  //console.error('str.length: ', str.length);
  //var str_out = str;
  var str_out = new Buffer(str, 'binary');
  timer('test', function() {
    for (var i = 0; i < iter; i++) {
      str_out.toString('binary');
      //new Buffer(str_out, 'binary').toString('binary');
      //new Buffer(str_out);
      //new Buffer(str_out, 'binary');
    }
  }, iter);

  str += str.slice(0, jump);
  if (--max > 0)
    setTimeout(runIt, 100);
}
runIt();


/*
var b = new Buffer(real_string, 'binary');
var c = b.toString('binary');
var d = new Buffer(c);

for (var i = 0; i < iter; i++) {
  //new Buffer(d);
  //new Buffer(c);
  //new Buffer(real_string);
}
/* */


/*
var extern_string = Buffer(real_string, 'binary').toString('binary');


setTimeout(function() {
  timer(fromString, iter);
});
//setTimeout(function() {
  //timer(fromExternal, iter);
//});


function fromString() {
  for (var i = 0; i < iter; i++)
    new Buffer(real_string);
}


function fromExternal() {
  for (var i = 0; i < iter; i++)
    new Buffer(extern_string);
}
/* */
