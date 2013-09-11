var shareMemory = require('./build/Release/share_memory');
var timer = require('../tools/test-script');
var runWithFlags = shareMemory.runWithFlags;
var runWithoutFlags = shareMemory.runWithoutFlags;
var obj_flags = {};
var iter = 1e6;

// Match the indexes in share_memory.cc
var kCallbackSet = 0;

function withCallback(val) {
  obj_flags[kCallbackSet] = 1;
}

// Setup external memory on the flags object
shareMemory.setupShared(obj_flags, withCallback);


// Run Tests //

timer('no flag', function() {
  for (var i = 0; i < iter; i++)
    runWithoutFlags(i);
}, iter);


timer('has flag', function() {
  for (var i = 0; i < iter; i++)
    runWithFlags(i);
}, iter);
