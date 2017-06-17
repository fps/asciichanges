
try {
    var peg = require('pegjs');
    var fs = require('fs');

    var note_pegjs = fs.readFileSync('note.pegjs', 'utf8');
    var bars_pegjs = fs.readFileSync('bars.pegjs', 'utf8');
    var chord_pegjs = fs.readFileSync('chord.pegjs', 'utf8');
    
    var asciichanges = peg.generate(note_pegjs + bars_pegjs + chord_pegjs, { trace: false });

    tests = {
        empty: '',

        C: 'C',

        empty_measure: '| |',

        one_measure: '  | C  | ',

        two_measures: ' | C  |    C   | ',

        repetition:  ' |   C   |:   C  |  C  :| ',

        multiline_bars: `
            |    |    |  
            |       |    |  
            | Am7b5    |
        `,

        empty_repetition:  `
            |     |     |     |     |
            |:    |     |1.   |    :|
                        |2.   |     |

            |:    |     |     |    :|
            |:    |1.  :|2.  :|3.   |
            `
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

