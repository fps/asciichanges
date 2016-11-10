var peg = require('pegjs');

try {
    var asciichanges = peg.generate(`
    
    {
        function noteLetterToInt(c) {
            if (c === 'C') { 
                return 0;
            }
            if (c === 'D') { 
                return 2;
            }
            if (c === 'E') { 
                return 4;
            }
            if (c === 'F') { 
                return 5;
            }
            if (c === 'G') { 
                return 7;
            }
            if (c === 'A') { 
                return 9;
            }
            if (c === 'B') { 
                return 11;
            }
        }
    }

    start
        =   empty_line* header:header? empty_line* harmony:harmony? empty_line* __
            {
                return { header: header, harmony: harmony };
            }
    
    header
        =   key_value (empty_line* key_value)*

    harmony
        =   (__ (chord:chord) __) / bars:bars
            {
                return { chord: chord, bars: bars };
            }

    lines
        =   line (eol+ line)+ 
    
    line
        =   non_empty_line / empty_line

    empty_line
        =   __ eol

    non_empty_line
        =   _* line:(bars / chord / key_value) _*
            { return  line; }
    
    chord
        =   note type? extension*

    note
        =   left:letter right:sharps_or_flats?
            { 
                return { 
                    root: left, 
                    accidental: right
                }; 
            }
    
    letter
        =   letter:[CDEFGAB]
            { 
                return noteLetterToInt(letter); 
            } 
    
    sharps_or_flats
        =   flats / sharps
    
    flats
        =   bees:('b'+) { return -1 * bees.length; }
    
    sharps
        =   sharps:('#'+) { return sharps.length; }
    
    type
        =   'maj' / 'min' / 'm' / 'sus4' / 'sus2' / 'sus' / 'dim' / 'aug'
    
    extension
        =   '7' / 'b9' / '9' / '#9' / '11' / '#11' / 'b13' / '13'
    
    key_value
        =   __ key:key ':' __ value:value __ eol
            { return { key: key, value: value }; }
    
    key
        =   [a-zA-Z] [a-zA-Z0-9]*
            {
                return text();
            }
    
    value
        =   fraction / real / integer / string

    string
        =   [a-zA-Z0-9 ]* 

    fraction
        =   integer '/' integer

    real
        =   integer '.' integer

    integer
        =   [0-9]+

    bars
        =   bar ( (chords / _+) bar )*
    
    chords
        =   _* chord ( _+ chord)* _*
    
    bar
        =   '|'
    
    ___
        =   _+
    __
        =   _*
    _
        = ' ' / '\\t'
    
    eol
        =   '\\n'
    
    `, { trace: false });


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
    
            | Cm7   | F7   | Bbmaj7 | Ebma7 |
            | Am7b5 | D7b9 | Gsus   | G7    |
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

