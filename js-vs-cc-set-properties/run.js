var js2cc = require('./build/Release/js_cc_set');
var setInCCSlow = js2cc.setInCCSlow;
var setInCCSym = js2cc.setInCCSym;
var setInJS = js2cc.setInJS;
var setInJSObj = js2cc.setInJSObj;

js2cc.setupCC(setProperties, setPropObj);

var iter = 1e6;
var time = process.hrtime();


// uncomment each of these to see the runtime

//setInCCSlow(iter, 1, 'cc', true);
//setInCCSym(iter, 1, 'cc', true);
//setInJS(iter, 1, 'js', true);
//setInJSObj(iter, 1, 'js', true);

time = process.hrtime(time);
console.log(((time[0] * 1e9 + time[1]) / iter)|0);


function setProperties(length, type, used) {
  this.length = length;
  this.type = type;
  this.used = used;
}


function setPropObj(length, type, used) {
  return {
    length: length,
    type: type,
    used: used
  };
}
