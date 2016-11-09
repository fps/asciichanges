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
        =   eol* lines eol*
    
    lines
        =   line (eol+ line)+ 
    
    line
        =   non_empty_line / empty_line

    empty_line
        =   _+

    non_empty_line
        =   _* line:(bars / chord / key_value) _*
            { return  line; }
    
    chord
        =   chord_with_type / chord_without_type
    
    chord_without_type
        =   note:note ext:(extension*) 
            { 
                return { chord: { note: note, extensions: ext } }; 
            }
    
    chord_with_type
        =   note:note type:type ext:(extension*) 
            { 
                return { chord: { note: note, type: type, extensions: ext } }; 
            }
    
    note
        =   left:letter right:sharps_or_flats 
            { 
                return { root: left, accidental: right }; 
            }
    
    letter
        =   letter:[CDEFGAB] { return noteLetterToInt(letter); } 
    
    sharps_or_flats
        =   sharps / flats
    
    flats
        =   bees:('b'*) { return -1 * bees.length; }
    
    sharps
        =   sharps:('#'*) { return sharps.length; }
    
    type
        =   'maj7' / (('min' / 'm' / 'sus4' / 'sus2' / 'sus' / 'dim' / 'aug')? '7'?)
    
    extension
        =   'b9' / '9' / '#9' / '11' / '#11' / 'b13' / '13'
    
    key_value
        =   key:key ':' _+ value:value
            { return { key: key, value: value }; }
    
    key
        =   ([a-z])+
    
    value
        =   ([a-z0-9])+
    
    bars
        =   bar ( (chords / _+) bar )*
    
    chords
        =   _* chord ( _+ chord)* _*
    
    bar
        =   '|'
    
    _
         = ' ' / '\\t'
    
    eol
        =   '\\n'
    
    `, { trace: true });
    
    doc = `
    C
    D
    E
    Eb
    Em
    Ebm
    Em7
    Ebm7
    Ebm9b13
    
    foo: bar
    
    D
    Eb
    Dbmin79
    |Cmaj7#9|
    `;
    
    console.log(JSON.stringify(asciichanges.parse(doc), null, 4));
}
catch (e)
{
    console.log(e);
}

