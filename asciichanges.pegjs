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
    =   ':'? '|' '|'? ':'?

split_bar
    =   bar empty_line+ __ bar

inner_bar
    =   split_bar / bar
___
    =   _+

__
    =   _*

_
    = ' ' / '\t'

eol
    =   '\n'

comment
    =   (';' / '//' / '#' / '--') c:[^\n]*
    {
        return {
            type: 'comment',
            comment: c
        };
    }

empty_line
    =   __ comment? eol

string
    =   [a-zA-Z0-9 ]* 
        {
            return { type: 'string', string: text() };
        }

fraction
    =   first:integer '/' second:integer
        {
            return { type: 'fraction', nominator:first, denominator:second };
        }

real
    =   first:integer '.' second:integer
        {
            return { type: 'real', integer: first, fraction: second };
        }

integer
    =   [0-9]+
        {
            return parseInt(text(), 10);
        }

content
    =   header:header? empty_line* harmony:harmony
        {
            return { type: 'asciichanges_song', header: header, harmony: harmony };
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
            type: 'optional_chord', 
            chord: c 
        };
    }

chord
    =   n:note q:quality? e:extension* sn:('/' s:note {return s;})?
        {
            return {
                type: 'chord',
                root: n,
                slash_note: sn,
                quality: q,
                extensions: e
            };
        }

note
    =   left:letter right:sharps_or_flats?
        { 
            return { 
                type: 'note',
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

quality
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
            return { type: 'key_value', key: key, value: value }; 
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
        return  { type: 'measures', measures: b };
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
    =   __ head:first_beat tail:(__ value:beat {return value;})* __
    {
        return [head].concat(tail);
    }

first_beat
    =   ([1-9]+ '.') / beat

beat
    =   optional_chord_or_chord

