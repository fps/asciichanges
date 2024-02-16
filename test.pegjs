document = whitespace* chords:chords whitespace* { return chords; }

chords = head:chord tail:(whitespace+ c:chord { return c; })* { return [head].concat(tail); }

whitespace =
	' ' / '\t' / '\n'

chord =
	root:note type:chord_type extensions:extensions slash_root:('/' note:note {return note;})?
    {
    	return { id: "chord", root: root, type: type, extensions: extensions, slash: slash_root };
    }

chord_type =
    '2' { return [2]; }
    /
    '5' { return [7]; }
    /
    major
    /
    minor
    /
    'sus2' { return [2, 7]; }
    /
    ('sus4' / 'sus') { return [5, 7]; }
    /
    ('diminished' / 'dim' / 'o') { return [3, 6]; }
    /
    ('augmented' / 'aug' / '+') { return [4, 8]; }
    /
    '' { return [4, 7]; }

major =
    (major_triad '7' / ('△' '7'?)) { return [4, 7, 11]; }
    /
	major_triad

major_triad =
	('major' / 'maj' / 'M') { return [4, 7]; }

minor =
	((minor_triad '7b5') / ('Ø' '7'?)) { return [3, 6, 10]; }
    /
	minor_triad

minor_triad =
	('minor' / 'min' / 'm' / '-') { return [3, 7]; }

note =
    letter:note_letter accidentals:accidentals?
    {
    	return (letter + accidentals + 12) % 12;
    }

note_letter =
	('C' / 'c') { return 0; }
	/
	('D' / 'd') { return 2; }
	/
	('E' / 'e') { return 4; }
	/
	('F' / 'f') { return 5; }
	/
	('G' / 'g') { return 7; }
	/
	('A' / 'a') { return 9; }
	/
	('B' / 'b') { return 11; }

accidentals
    =   flats
    	/
        sharps

flats
    =   flats:(flat+) { return -1 * flats.length; }

sharps
    =   sharps:(sharp+) { return sharps.length; }

flat =
    '♭' / 'b'

sharp =
    '♯' / '#'

extensions =
	'(' e:extension* ')' { return e; }
    /
    extension*

extension =
	'6' { return 9; }
    /
    '7' { return 10; }
    /
    ('maj' / 'major') '7' { return 11; }
    /
    flat '9' { return 1; }
    /
    '9' { return 2; }
    /
    sharp '9' { return 3; }
    /
    '11' { return  5; }
    /
    sharp '11' { return 6; }
    /
    flat '13' { return 8; }
    /
    '13' { return 9; }
