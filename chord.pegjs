
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

flats
    =   bees:('b'+) { return -1 * bees.length; }

sharps
    =   sharps:('#'+) { return sharps.length; }

quality
    =   '2' / '5' / 'major' / 'maj' / 'minor' / 'min' / 'm' / 'sus4' / 'sus2' / 'sus' / 'dim' / 'aug'

extension
    =   '6' / '7' / 'b9' / '9' / '#9' / '11' / '#11' / 'b13' / 'b5' / '13'