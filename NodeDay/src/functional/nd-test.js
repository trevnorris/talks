var personsList = require('./name-data-set.json');

function sumHours(people, nameReg, minHours) {
  var result = [];

  Object.keys(people).filter(function(element) {
    // Filter out everyone that doesn't match the regex.
    return nameReg.test(element[0]);
  }).filter(function(name) {
    // Filter out all those who don't have enough hours.
    return people[name].hours >= minHours;
  }).sort(function(a, b) {
    // Sort the names of the people by the most hours.
    return people[b].hours - people[a].hours;
  }).forEach(function(name) {
    result.push({
      name: name,
      hours: people[name].hours
    });
  });

  return result;
}


function sumHours2(people, nameReg, minHours) {
  var result = [];
  var puid = [];
  var phrs = [];
  var names = Object.keys(people);
  var i, p;

  for (i = 0; i < names.length; i++) {
    p = names[i];
    if (nameReg.test(p))
      puid.push(p);
  }

  for (i = 0; i < puid.length; i++) {
    p = puid[i];
    if (people[p].hours >= minHours)
      phrs.push(p);
  }

  for (i = 0; i < phrs.length; i++) {
    result.push({ name: phrs[i], hours: people[phrs[i]].hours });
  }

  return result.sort(function(a, b) { return b.hours - a.hours })
}


function sumSort(a, b) { return b.hours - a.hours }


function sumHours1(people, nameReg, minHours) {
  var result = [];

  Object.keys(people).filter(function(name) {
    // Filter out all those who don't have enough hours.
    // Filter out everyone that doesn't match the regex.
    return people[name].hours >= minHours && nameReg.test(name[0]);
  // Add each person with the number of hours they've worked to the array.
  }).forEach(function(name) {
    result.push({
      name: name,
      hours: people[name].hours
    });
  });

  // Sort the names of the people by the most hours.
  return result.sort(sumSort);
}


function sumHours3(people, nameReg, minHours) {
  var result = [];
  var names = Object.keys(people);
  var i, n;

  for (i = 0; i < names.length; i++) {
    n = names[i];
    if (people[n].hours >= minHours && nameReg.test(n))
      result.push({ name: n, hours: people[n].hours });
  }

  return result.sort(sumSort)
}


// As a side note, RegExp sucks.
function sumHours4(people, minHours) {
  var result = [];
  var names = Object.keys(people);
  var i, n, v;

  for (i = 0; i < names.length; i++) {
    n = names[i];
    v = n.charCodeAt(0);
    if (((v >= 97 && v <= 109) || (v >= 65 && v <= 77)) &&
        people[n].hours >= minHours)
      result.push({ name: n, hours: people[n].hours });
  }

  return result.sort(sumSort)
}


// Want all people who's names start with A-M
var reg = /^[a-m]/i;
var minHours = 20;
var ITER = 1e5;

var t = process.hrtime();

for (var i = 0; i < ITER; i++) {
  //sumHours(personsList, reg, minHours);
  //sumHours2(personsList, reg, minHours);
  //sumHours1(personsList, reg, minHours);
  sumHours3(personsList, reg, minHours);
  //sumHours4(personsList, minHours);
}

t = process.hrtime(t);

console.log(((t[0] * 1e9 + t[1]) / ITER).toFixed(1) + ' ns/op');
