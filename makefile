web/asciichanges-parser.js: asciichanges.pegjs
	./node_modules/.bin/pegjs -e pegjs --format globals -o docs/asciichanges.js asciichanges.pegjs
