
try {
    var peg = require('pegjs');
    var fs = require('fs');

    var asciichanges_pegjs = fs.readFileSync('bars.pegjs', 'utf8');

    var asciichanges = peg.generate(asciichanges_pegjs , { trace: false });

    tests = {
        empty: '',

        C: 'C',

        empty_measure: '| |',

        one_measure: '  | C  | ',

        two_measures: ' | C  |    C   | ',

        repetition:  ' |   C   |:   C  |  C  :| '
    }
    
    for (var key in tests) {
        console.log('test: ' + key);
        console.log(JSON.stringify(asciichanges.parse(tests[key]), null, 4));
    }
}
catch (e)
{
    console.log(e);
}

