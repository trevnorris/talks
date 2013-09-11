var shareObjects = require('./build/Release/share_objects');
var timer = require('../tools/test-script');
var accessNamed = shareObjects.accessNamed;
var accessIndexed = shareObjects.accessIndexed;
var callback_wrap = {};
var callback_flags = {};
var iter = 1e6;

// Match the indexes in share_memory.cc
var kError = 0;
var kConnection = 1;

// Persist the indexed object for the callbacks
shareObjects.setup(callback_wrap, callback_flags);


// Run Tests //

timer('accessNamed', function() {
  for (var i = 0; i < iter; i++)
    accessNamed();
}, iter);


timer('accessIndexed', function() {
  for (var i = 0; i < iter; i++)
    accessIndexed();
}, iter);
