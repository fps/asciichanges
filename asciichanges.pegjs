 
start = 
    h:(l:line newline {return l;})* l:line newline?
    {
        return h.concat(l);
    }
    
line =
    comment / key_value / harmony / whitespaces
    
whitespaces =
    whitespace*
    {
        return {
            type: 'whitespace'
        };
    }

whitespace = 
    ' ' / '\t'

newline =
    '\n'

empty_line =
    whitespace* newline

comment
    =   (';' / '//' / '#' / '--') c:([^\n]* {return text();})
    {
        return {
            type: 'comment',
            comment: c,
            location: location()
        };
    }

key_value
    =   key:key ':' whitespace value:value
        { 
            return { 
                type: 'key_value', 
                key: key, 
                value: value,
                location: location()
            }; 
        }

key
    =   [a-zA-Z] [a-zA-Z0-9]*
        {
            return text();
        }

value
    =   fraction / real / integer / string

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
            return { type: 'integer', integer: parseInt(text(), 10) };
        }

bar =
    '|'
    {
        return {
            type: 'bar',
            location: location()
        };
    }

harmony =
    whitespace* bar h:(m:measure bar { return m;})+ whitespace*
    {
        return {
            type: 'harmony',
            harmony: h
        };
    }
    
measure =
    l1:loop_mark? ln:loop_number? whitespace+ s:(s:stuff whitespace+ {return s;})* l2:loop_mark?
    {
        return {
            type: 'measure',
            loop_start: l1 != null,
            loop_end: l2 != null,
            loop_number: ln,
            stuff: s,
            location: location()
        }
    }

loop_mark =
    ':'
    
loop_number =
    i:integer '.'
    {
        return {
            type: 'loop_number',
            number: i.integer
        };
    }

stuff =
    dal_segno / da_capo / chord / coda / segno / optional_chord / beat
    
beat =
    '/'
    {
        return {
            type: 'beat'
        };
    }

dal_segno "dal segno" =
    ('D.S.' / '𝄉')
    {
        return {
            type: 'dal_segno',
            location: location()
        };
    }
    
    
da_capo "da capo" =
    ('D.C.' / '𝄊')
    {
        return {
            type: 'da_capo',
            location: location()
        };
    }

coda "coda" =
    ('𝄌' / '@' / '(+)')
    {
        return {
            type: 'coda',
            location: location()
        };
    }

segno "segno" =
    ('𝄋' / '%' / '(S)')
    {
        return {
            type: 'segno',
            location: location()
        };
    }
    
optional_chord =
    '(' c:chord ')'
    {
        c.optional = true;
        return c;
    }
    
chord "chord"
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

note "note"
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
            if (letter === 'C') { 
                return 0;
            }
            if (letter === 'D') { 
                return 2;
            }
            if (letter === 'E') { 
                return 4;
            }
            if (letter === 'F') { 
                return 5;
            }
            if (letter === 'G') { 
                return 7;
            }
            if (letter === 'A') { 
                return 9;
            }
            if (letter === 'B') { 
                return 11;
            }
        } 

sharps_or_flats
    =   flats / sharps

flat =
    '♭' / 'b'
    
sharp =
    '♯' / '#'
    
flats
    =   bees:(flat+) { return -1 * bees.length; }

sharps
    =   sharpies:(sharp+) { return sharpies.length; }

quality
    =   '2' / '5' / 'major' / 'maj' / 'minor' / 'min' / 'm' / 'sus4' / 'sus2' / 'sus' / 'dim' / 'aug'

extension
    =   '6' / '7' / 'alt' / 'maj7' / (flat '9') / '9' / (sharp '9') / '11' / (sharp '11') / (flat '13') / (flat '5') / '13'
    