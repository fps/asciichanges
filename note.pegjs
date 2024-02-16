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

