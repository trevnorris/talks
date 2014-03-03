function square(x) {
  return x * x;
}

function addSquares(a, b) {
  return square(a) + square(b);
}


var ITER = 1e6;
//var t = process.hrtime();

for (var i = 0; i < ITER; i++) {
  addSquares(i, i + 1);
}

//t = process.hrtime(t);

//console.log(((t[0] * 1e9 + t[1]) / ITER).toFixed(1) + ' ns/op');
