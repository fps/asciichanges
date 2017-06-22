web/asciichanges-parser.js: asciichanges.pegjs
	pegjs -e asciichanges --format globals -o docs/asciichanges-parser.js asciichanges.pegjs
