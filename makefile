web/asciichanges-parser.js: asciichanges.pegjs
	./node_modules/.bin/pegjs -e asciichanges --format globals -o docs/asciichanges-parser.js asciichanges.pegjs
