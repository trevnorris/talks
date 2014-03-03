function ClosureColor(name) {
  // Have no choice but to add these methods to the instance
  this.getName = function () {
      return name;
  };
  this.setName = function (n) {
      name = n;
  };
}

function PrototypeColor(name) {
  this._name = name;
}

PrototypeColor.prototype.getName = function () {
  return this._name;
};

PrototypeColor.prototype.setName = function (n) {
  this._name = n;
};


var ITER = 1e6;
var t = process.hrtime();

for (var i = 0; i < ITER; i++) {
  new ClosureColor('green');
  //new PrototypeColor('green');
}
/* */

//var inst = new ClosureColor('green');
//var inst = new PrototypeColor('green');
//for (var i = 0; i < ITER; i++) {
  //inst.setName('red');
  //inst.getName();
//}

t = process.hrtime(t);

console.log(((t[0] * 1e9 + t[1]) / ITER).toFixed(1) + ' ns/op');
