++++[>++++[>+++<-]<-]   # Writing 48 / 0x30 / '0' in cell(2)

,>,>                     # Reading two numbers into cell(0) and cell(1)

[<-<->>-]                # Decrementing cell(0) and cell(1) by 48 / 0x30 / '0'

<<                       # Go to cell(0)

[                        # Multiplication loop
    >                    # Go to cell(1)
    [>+>+<<-]            # Move cell(1) to cell(2) and cell(3)
    >>                   # Go to cell(3)
    [<<+>>-]             # Move cell(3) back to cell(1)
    <<<-                 # Decrement cell(0)
]

>[-]<                    # Set cell(1) to 0 (counter, we are in cell 0 here)

++++[>++++[>+++<-]<-]   # Adding 48 / 0x30 / '0' to cell(2), cell 2 has the result

>>.                      # Print result (go to cell 2 and print)

