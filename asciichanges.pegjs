/*
document =
	head:line tail:(newline line:line { return line; })* newline?
    { return  head.concat(tail).filter(e => e); }
*/

document = lines:line* { return lines.flat(); }

line =
	whitespace* content:content whitespace* newline? { return content; } / newline

whitespace =
	(' ' / '\t')

newline =
	'\n'

content =
	c:chords { return [c]; } / bars

// BARS

bars =
	'|' bars:(bar)+   { return bars; }

bar =
	whitespace* chords:chords? whitespace* '|'
    { return chords; }

chords =
	head:chordlike tail:(whitespace+ chord:chordlike { return chord; })*
    { return [head].concat(tail); }

// CHORDS

chordlike =
	chord / beat

beat =
    '/'   { return { type: 'beat' }; }


chord =
	root:note quality:quality? additions:addition* suspended:suspended? slash:('/' note:note { return note; })?
    {
    	var ret = {
        	type: 'chord',
            text: text(),
        	root: root,
        	quality: quality ? quality : { third: 4, fifth: [7] },
            additions: additions,
            slash: slash,
        };

        if (suspended) {
        	ret.third = suspended;
        }

        return ret;
    }

quality =
        seventh:sixth_or_seventh fifth:fifth? extensions:extensions?
        { return { third: 4, fifth: fifth ? fifth : [7], seventh: seventh, extensions: extensions }; }

	  / minor seventh:sixth_or_seventh? fifth:fifth? extensions:extensions?
        { return { third: 3, fifth: fifth ? fifth : [7], seventh: seventh ? seventh : extensions ? 10 : null, extensions: extensions }; }

	  / augmented seventh:sixth_or_seventh? extensions:extensions?
        { return { third: 4, fifth: [8], seventh: seventh ? seventh : extensions ? 10 : null, extensions: extensions }; }

	  / diminished seventh:'7'? extensions:extensions?
        { return { third: 3, fifth: [6], seventh: seventh ? 9 : extensions ? 9 : null, extensions: extensions }; }

        / fifth:bracketed_fifth? extensions:extensions
        { return { third: 4, fifth: fifth ? fifth : [7], seventh: 10, extensions: extensions }; }

	  / fifth:bracketed_fifth
        { return { third: 4, fifth: fifth ? fifth : [7], seventh: null, extensions: null }; }

suspended =
	'sus4' { return 5; } / 'sus2' { return 2; } / 'sus' { return 5; }

bracketed_fifth =
	'(' fifth:fifth ')' { return fifth; } / fifth

fifth =
	flat '5' sharp '5' { return [6, 8]; } / flat '5' { return [6]; } / sharp '5' { return [8]; }

sixth_or_seventh =
	'6' { return 9; } / seventh

seventh =
	('M7' / 'M' / major '7' / major) { return 11; } / '7' { return 10; }

extensions =
	  n:nineth? t:tenth? e:eleventh? th:thirteenth
      { return th.concat(e).concat(t).concat(n).filter(x => x); }
    / n:nineth? t:tenth? e:eleventh
      { return e.concat(t).concat(n).filter(x => x); }
    / n:nineth? t:tenth
      { return t.concat(n).filter(x => x); }
    / nineth

nineth =
	  flat '9' sharp '9' { return [13, 15]; }
    / flat '9' { return [13]; }
    / sharp '9' { return [15]; }
    / '9' { return [14]; }

tenth =
	flat '10' { return [15]; }  / '10' { return [16]; }

eleventh =
	sharp '11' { return [18]; } / '11' { return [17]; }

thirteenth =
	flat '13' { return [20]; } / '13' { return [21]; }

addition =
	'add'
	note:(
    	  flat '2' { return 1; }
        / sharp '2' { return 3; }
        / '2' { return 2; }
        / flat '3' { return 3; }
        / '3' { return 4; }
        / '4' { return 5; }
        / sharp '4' { return 6; }
        / flat '5' { return 6; }
        / sharp '5' { return 8; }
        / '5' { return 7; }
        / flat '6' { return 8; }
        / '6' { return 9; }
    	/ '9' { return 14; }
        / flat '9' { return 13; }
        / sharp '9' { return 15; }
        / flat '10' { return 15; }
        / '10' { return 16; }
        / '11' { return 17; }
        / sharp '11' { return 18; }
        / '12' { return 19; }
        / flat '13' { return 20; }
        / '13' { return 21; }
    )
    { return note; }

note =
    letter:note_letter accidentals:accidentals?
    {
    	return (letter + accidentals + 12) % 12;
    }

note_letter =
	  ('C' / 'c') { return 0; }
	/ ('D' / 'd') { return 2; }
	/ ('E' / 'e') { return 4; }
	/ ('F' / 'f') { return 5; }
	/ ('G' / 'g') { return 7; }
	/ ('A' / 'a') { return 9; }
	/ ('B' / 'b') { return 11; }

accidentals
    =   flats:(flat+) { return -1 * flats.length; }
    	/
        sharps:(sharp+) { return sharps.length; }

flat =
    '♭' / 'b'

sharp =
    '♯' / '#'

major =
	'major' / 'maj'

minor =
	'minor' / 'min' / 'm' / '-'

augmented =
	'aug' / '+'

diminished =
	'dim' / 'o'

half_diminished =
	'0' / 'ø'



