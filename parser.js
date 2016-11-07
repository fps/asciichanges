var peg = require('pegjs');
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
    =   line*

line
    =   line:(key_value / chord / bars)? eol
        { return  line; }

eol
    =   '\\n'

chord
    =   note:note type:type? ext:(extension*) { return { chord: { note: note, type: type, extensions: ext } }; }

note
    =   left:letter right:sharps_or_flats { return { root: left, accidental: right }; }

letter
    =   letter:[CDEFGAB] { return noteLetterToInt(letter); } 

sharps_or_flats
    =   sharps / flats

sharps
    =   bees:('b'*) { return -1 * bees.length; }

flats
    =   sharps:('#'*) { return sharps.length; }

type
    =   'm' / 'sus4' / 'sus2' / 'sus' / 'dim' / 'aug'

extension
    =   '7' / 'b9' / '9' / '#9' / '11' / '#11' / 'b13' / '13'

key_value
    =   key ":" value

key
    =   [a-zA-Z]+

value
    =   [a-zA-Z0-9]+

bars
    =   bar ( (chord* / ' '+) bar )*

bar
    =   '|'

`);

doc = `
C
D
Eb
Dbm79
|C|
`;

console.log(JSON.stringify(asciichanges.parse(doc), null, 4));
