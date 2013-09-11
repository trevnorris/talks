var timer = require('../tools/test-script');
var size = 4;

// Create a ridiculous JSON object with utf8 values.
var json = {};
for (var i = 0; i < size; i++)
  json[i] = 'foo:\u0222 bar:\u0223';

// First setup the data to look  like it would after being read in
// from a file.
var json_string = JSON.stringify(json);
// We're going to assume the file was written in UTF8.
var json_buffer = new Buffer(json_string, 'utf8');


// Start working with the data.
var binary_json = json_buffer.toString('binary');
// Unfortunately JSON.parse always assumes UTF8.
// But I'm working on a hack for that.
var json_binary = JSON.parse(binary_json);

// Here we'll see the values look all fubar, but before they're written
// out to a stream we can convert them back to a Buffer using binary
// encoding and they'll have the same representation.
console.log(json_binary);


// Loop through the values and show that we can get the correct bytes
// back out.
for (var i = 0; i < size; i++)
  console.log(Buffer(json_binary[i], 'binary').toString('utf8'));
