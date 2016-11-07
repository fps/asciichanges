var peg = require('pegjs');
var asciichanges = require('./asciichanges.js');

doc = 'Cm79';

console.log(asciichanges.parse(doc));
