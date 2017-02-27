web/asciichanges-parser.js: asciichanges.pegjs
	pegjs -e asciichanges --format globals -o web/asciichanges-parser.js asciichanges.pegjs
