start
    =   line*

line
    =   key_value
        /
        chord
        /
        bars

chord
    =   note type extension+

note 
    =   [CDEFGAB] ('b'* / '#'*) 

type
    =   'm' / 'min' / 'sus' / 'sus2' / 'sus4' / 'dim' / 'aug'

extension
    =   '7' / 'b9' / '9' / '#9' / '11' / '#11' / 'b13' / '13'

key_value
    =   key ":" value

key
    =   [a-zA-Z]+

value 
    =   [a-zA-Z0-9]+

bars
    =   bar ( (chord* / ' '+) bar )*

bar
    =   '|'
        
