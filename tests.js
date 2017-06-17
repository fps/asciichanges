
try {
    var peg = require('pegjs');
    var fs = require('fs');

    var asciichanges_pegjs = fs.readFileSync('asciichanges.pegjs', 'utf8');
    
    var asciichanges = peg.generate(asciichanges_pegjs, { trace: false });

    tests = {
        C: '| C |',

        empty_measure: '| |',

        one_measure: '  | C  | ',

        two_measures: ' | C♭  |    C#   | ',

        repetition:  ' |   C   |:   C♯  |  C  :| ',

        multiline_bars: `
            |    |    |  
            |       |    |  
            | Am7b5    |
        `,

        empty_repetition:  `
            |     |     |     |     |
            |:    |     |1.   |    :|
                        |2.   |     |

            |:    |     |     |       :|
            |:    |1.  :|2.  :|3.    |
            | %   |     | @   | D.S. |
            | @   |     |
            `,
            
        autumn_leaves: `
-- Autumn Leaves

Tempo: 120
Time: 4/4

-- A:
|: Cm7     | F7       |   Bbmaj7     | Ebmaj7        |
| Am7b5   | D7b9      |1. Gm         | G7b9         :|
                      |2. Gm         |               |

-- B:
| Am7b5    | D7b9     | Gm           | G7b9          |
| Cm7      | F7       | Bbmaj7       | Ebmaj7        |
| Am7b5    | D7♭9     | Gm / Gm/Gb / | Gm/F / Gm/E / |
| Ebmaj7   | D7b9     | 𝄌 Gm         | (G7b9)  D.C.  |

| 𝄌 Gdim | Gminmaj79 |`,

        eb9: '| Eb9 |'
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

