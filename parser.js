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
        =   empty_line* c:content? empty_line* __
            {
                return c;
            }

    bar
        =   '|'

    split_bar
        =   '|' empty_line+ __ '|'
    
    inner_bar
        =   split_bar / bar
    ___
        =   _+

    __
        =   _*

    _
        = ' ' / '\\t'
    
    eol
        =   '\\n'

    comment
        =   '--' [^\\n]*
    
    empty_line
        =   __ comment? eol

    string
        =   [a-zA-Z0-9 ]* 
            {
                return { ttag: 'string', string: text() };
            }

    fraction
        =   first:integer '/' second:integer
            {
                return { ttag: 'fraction', nominator:first, denominator:second };
            }

    real
        =   first:integer '.' second:integer
            {
                return { ttag: 'real', integer: first, fraction: second };
            }

    integer
        =   [0-9]+
            {
                return parseInt(text(), 10);
            }

    content
        =   header:header? empty_line* harmony:harmony
            {
                return { ttag: 'asciichanges_song', header: header, harmony: harmony };
            }
    
    header
        =   head:__key_value__ tail:(empty_line* k:__key_value__ { return k; })*
            {
                return [head].concat(tail);
            }

    harmony
        =   __chord__ / bars

    __chord__
        =   __ c:chord __
            {
                return c;
            }

    optional_chord_or_chord
        = optional_chord / chord

    optional_chord
        =   '(' __ c:chord __ ')'
        {
            return { 
                ttag: 'optional_chord', 
                chord: c 
            };
        }

    chord
        =   note:note type:type? extensions:extension* slash:('/' s:note {return s;})?
            {
                return {
                    ttag: 'chord',
                    root: note,
                    slash_note: slash,
                    type: type,
                    extensions: extensions
                };
            }

    note
        =   left:letter right:sharps_or_flats?
            { 
                return { 
                    ttag: 'note',
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
        =   '2' / '5' / 'major' / 'maj' / 'minor' / 'min' / 'm' / 'sus4' / 'sus2' / 'sus' / 'dim' / 'aug'
    
    extension
        =   '6' / '7' / 'b9' / '9' / '#9' / '11' / '#11' / 'b13' / 'b5' / '13'

    __key_value__
            = __ k:key_value __ eol
            {
                return k;
            }
    
    key_value
        =   key:key ':' __ value:value
            { 
                return { ttag: 'key_value', key: key, value: value }; 
            }
    
    key
        =   [a-zA-Z] [a-zA-Z0-9]*
            {
                return text();
            }
    
    value
        =   fraction / real / integer / string

    bars
        =   __ bar b:bars_content bar __ eol? __?
        {
            return  { ttag: 'measures', measures: b };
        }

    bars_content
        =   several_measures / single_measure

    several_measures
        =   head:single_measure tail:(inner_bar value:single_measure {return value;} )*
            {
                return [head].concat(tail);
            }

    single_measure
        =   beats / empty_bar

    empty_bar
        =   ___
        {
            return [];
        }

    beats
        =   __ head:beat tail:(__ value:beat {return value;})* __
        {
            return [head].concat(tail);
        }

    beat
        =   optional_chord_or_chord

   
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
            | Cm7   | F7   | Bbmaj7   | Ebmaj7     |
            | Am7b5 | D7b9 | Gsus     | G7         |
            | Cm7   | F7   | Bbmaj7   | Ebmaj7     |
            | Am7b5 | D7b9 | Gm       |            |

            -- B:
            | Am7b5 | D7b9 | Gsus     | G7         |
            | Cm7   | F7   | Bbmaj7   | Ebmaj7     |
            | Am7b5 | D7b9 | Gm Gm/Gb | Gm/A Gm/Ab |
            | Am7b5 | D7b9 | Gm       | (G7)       |
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

