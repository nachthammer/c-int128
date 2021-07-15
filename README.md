# Integer with a length of 128 bit - library for reading and writing

Did you ever use 128 bit integers in C? Probably not, and there is a good reason for it, so don't use them. Thank you!

You are still here? Well, then I have no choice but to explain my library to you.

## usage 
 - download the `int128_lib.h` in your working directory
 - past `#include "int128_lib.h"` into your file where you need to read/write your __int128
 - `main.c` has an example of how to read an integer from the command line
 - if you want a working project, just get the `Makefile` in addition to the `main.c` and `int_128_lib.h` and do `make` on Linux
 - you can input everything into the strtoi128 function, as long as it's a `char*` pointer (command line argument for example)

If you want to know more about the functions, just look in the `int128_lib.h` file and read the docs.

I hope this helps you with reading and printing 128 bit integer. If you want to work with 128 bit ineteger in assembler, just write me an Email, I've done that, too.

Star and fork if you used something of this and if you have trouble with 128 bit integer, just create an issue and I might get on it.
