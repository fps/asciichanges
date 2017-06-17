start = 
    prespace c:content? postspace
    {
        return c;
    }

prespace =
    empty_line_end*
    whitespace*

postspace =
    empty_line_end*
    whitespace*

whitespace = 
    ' ' / '\t'

newline =
    '\n'

empty_line_end =
    whitespace* newline

bar =
    '|' empty_line_end+ whitespace* '|' / '|'

content =
    harmony / song

song = 
    '|' measure+

measure =
    repetition / simple_measure

measure_content = 
    (whitespace+ harmony whitespace+) / whitespace+

simple_measure =
    measure_content bar

repetition = 
    ':' simple_measure* (simple_repetition_end / numbered_repetition_ends)

numbered_repetition_ends =
    ([0-9]+ '.' simple_measure* simple_repetition_end)+ [0-9]+ '.'
    
simple_repetition_end = 
    measure_content ':' bar

numbered_repetition_end = 
    [0-9]+ '.' measure_content ':' bar

harmony =
    ((chord whitespace+)+ chord) / chord

