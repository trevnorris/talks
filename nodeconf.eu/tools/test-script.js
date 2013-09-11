var tests = [];

module.exports = function timeTest(msg, cb, iter) {
  tests.push(function() {
    setTimeout(function() {
      var t = process.hrtime();
      cb();
      printTime(msg, process.hrtime(t), iter);
      runTests();
    }, 300);
  });
};

function runTests() {
  if (tests.length === 0)
    return;
  tests.shift()();
}

process.nextTick(runTests);


function printTime(msg, hrtime, iter) {
  process.nextTick(function() {
    var ns = (hrtime[0] * 1e9 + hrtime[1]) / iter;
    var place = 1;
    var time;
    if ((ns % (place = 1e9)) !== ns)
      time = 'sec';
    else if ((ns % (place = 1e6)) !== ns)
      time = 'ms';
    else if ((ns % (place = 1e3)) !== ns)
      time = '\u03bcs';
    else
      place = 1, time = 'ns';

    console.error('%s - %s %s/op', msg, (ns / place).toFixed(2), time);
  });
}
