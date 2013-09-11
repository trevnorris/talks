var js2cc = require('./build/Release/js_cc_set');
var timer = require('../tools/test-script');
var setInCCSlow = js2cc.setInCCSlow;
var setInCCSym = js2cc.setInCCSym;
var setInJS = js2cc.setInJS;
var setInJSObj = js2cc.setInJSObj;
var iter = 1e6;

js2cc.setupCC(setProperties, setPropObj);


timer('setInCCSlow', function() {
  setInCCSlow(iter, 1, 'cc', true);
}, iter);


timer('setInCCSym', function() {
  setInCCSym(iter, 1, 'cc', true);
}, iter);


timer('setInJS', function() {
  setInJS(iter, 1, 'js', true);
}, iter);


timer('setInJSObj', function() {
  setInJSObj(iter, 1, 'js', true);
}, iter);



// object is created in cc and set as instance of function when called
function setProperties(length, type, used) {
  this.length = length;
  this.type = type;
  this.used = used;
}


// returns new object setting object properties passed from cc
function setPropObj(length, type, used) {
  return {
    length: length,
    type: type,
    used: used
  };
}
