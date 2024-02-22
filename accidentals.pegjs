accidentals
    =   flats:(flat+) { return -1 * flats.length; }
    	/
        sharps:(sharp+) { return sharps.length; }

flat =
    '♭' / 'b'

sharp =
    '♯' / '#'
