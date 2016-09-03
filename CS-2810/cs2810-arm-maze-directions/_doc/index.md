Maze directions
===============

Change your function to accept two parameters:

    directions(directions_pointer, count)

`directions_pointer` is a pointer (memory address) to the beginning
of a list of directions, where each direction is one byte long.
`count` tells the number of entries in the array.

Your function should loop over the list, and print a line of output
for each entry in the list. Here is what you should print for each
possible value:

* 00000000 (0) → "up\n"
* 00000001 (1) → "down\n"
* 00000010 (2) → "left\n"
* 00000011 (3) → "right\n"
* 00000100 (4) → "go to the start\n"
* 00000101 (5) → "you are finished!\n"
* anything else → "invalid directions\n"

So if the list containes these bytes (listed in hex)

    04 01 01 02 03 05

and if the value of `directions_pointer` (the r0 register) is
address in memory where the list is located and the value of
`count` is six, your function should print this to stdout:

    go to the start
    down
    down
    left
    right
    you are finished!
