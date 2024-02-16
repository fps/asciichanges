document =
	head:line tail:(newline line:line { return line; })* newline?
    { return { type: 'lines', value: [head].concat(tail).filter(e => e)}; }

line =
	whitespace* t:content? whitespace* { return t; }

whitespace =
	(' ' / '\t')

newline =
	'\n'

content =
	c:chords / bars

// BARS

bars =
	'|' bars:(bar)+   { return { type: 'bars', value: bars }; }

bar =
	whitespace* chords:chords? whitespace* '|'
    { return { type: 'bar', value: chords }; }

chords =
	head:chordlike tail:(whitespace+ chord:chordlike { return chord; })*
    { return { type: 'chords', value: [head].concat(tail) }; }

// CHORDS

chordlike =
	chord / beat

beat =
    '/'   { return { type: 'chord', value: null }; }

chord =
	n:note notes:chord_notes? slash_root:('/' m:note { return m})?
    { return { type: 'chord', value: { root: n, slash_root: slash_root, notes: notes } }; }

chord_notes =
	  structure
    / half_dim
    / dim
	/ m:(minor { return [3, 7]; }) s:structure?
	/ '' { return [ 4, 7, ]; }

structure =
	  extensions additions*
    / additions+

extensions =
	  flat '9'
    / sharp '9'
    / '9'

additions =
	'add'
	note:(
    	  '9' { return 14; }
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

half_dim =
	(minor '7b5' / '0') { return [3, 6]; }

dim =
	  'dim'
    / '0'

aug =
	  'aug'
    / '+'

major =
	'major' / 'maj' / 'M'

minor =
	'minor' / 'min' / 'm' / '-'

// NOTES

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
