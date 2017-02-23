
try {
    var peg = require('pegjs');
    var fs = require('fs');

    var asciichanges_pegjs = fs.readFileSync('asciichanges.pegjs', 'utf8');

    var asciichanges = peg.generate(asciichanges_pegjs , { trace: false });

    tests = {
        empty: '',

        c: 'C',
        csharp: 'C#',
        cflat: 'Cb',
        d: 'D',
        e: 'E',
        cm: 'Cm',
        ebm: 'Ebm',
        csharpm: 'C#m',

        eflatmajorsevensharpeleven: 'Ebmaj7#11',

        single_chord_multiline: `
            Ebmaj7#11
        `,

        single_chord_with_header: ` 
            title: test
            tempo: 125.5
            time: 3/4

            C#m79
        `,

        full_song: `
            title: The Autumn Leaves
            tempo: 80 
            time: 4/4
    
            | Cm7   | F7   | Bbmaj7   | Ebmaj7     |
            | Am7b5 | D7b9 | Gsus     | G7         |
            | Cm7   | F7   | Bbmaj7   | Ebmaj7     |
            | Am7b5 | D7b9 | Gm       |            |
            | Am7b5 | D7b9 | Gsus     | G7         |
            | Cm7   | F7   | Bbmaj7   | Ebmaj7     |
            | Am7b5 | D7b9 | Gm Gm/Gb | Gm/A Gm/Ab |
            | Am7b5 | D7b9 | Gm       |            |
        `,

        full_song_with_comments: `
            -- this is a complete song with comments!
            title: The Autumn Leaves
            tempo: 80 
            time: 4/4
    
            -- A:
            |: Cm7   | F7   |    Bbmaj7   | Ebmaj7     |
            |  Am7b5 | D7b9 | 1. Gsus     | G7         |
                            | 2. Gm       |           :|

            -- B:
            |  Am7b5 | D7b9 | Gsus        | G7         |
            |  Cm7   | F7   | Bbmaj7      | Ebmaj7     |
            |  Am7b5 | D7b9 | Gm Gm/Gb    | Gm/A Gm/Ab |
            |  Am7b5 | D7b9 | Gm          | (G7)       |
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

