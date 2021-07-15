/** this is a library where I wrote functions or redesigned them during a university project, because it was impossible to find any
useful material on 128 bit, There was no way to read them or print them
I hope that sometimes someone needs __int128 and now has proper functions
I do not guarantee for their always working especially because it's C
Be sure to star the project if you like it and put some issues if you find any.
*/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#include <errno.h>
#ifdef NEED_DECLARATION_ERRNO
extern int errno;
#endif
#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>
#pragma once // we need this so we dont have double implications

/**
 *  first we look whether 128 bit numbers are supported, test this in your code before
 * */
#ifdef __SIZEOF_INT128__
//printf("128 bit integers are supported, your program should work.\n");
#else
printf("128 bit are not supported, your program might give wrong outputs");
#endif
/**
 * decimal aux function, dont use it
 */
void print_int128_aux(__int128 x)
{
    //printf("we have to overdo this function, but for now it's good - print()\n");
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print_int128_aux(x / 10);
    putchar(x % 10 + '0');
}
/**
 * binary aux function, dont use it
 */
void print_int128_bin_aux(__int128 x)
{
    //printf("we have to overdo this function, but for now it's good - print()\n");
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 1)
        print_int128_bin_aux(x / 2);
    putchar(x % 2 + '0');
}
/** printing functions
there are multiple ways of printing __int128 numbers, sadly there is no way in C to do it like integers where you just do %i and put the number as an argument
  - an n at the and of the name of a function indicates that the print statement breaks line after the number.
  - an s at the and of the name of a function indicates that the print statement has a space after.
*/

/** 
 * print an __int128 as decimal without any line breaks or spaces
 */
void print_int128(__int128 x)
{
    print_int128_aux(x);
}

/** 
 * prints the __int128 as 2 hexadecimal numbers, where the first one represents the upper 64 bit and the second the the lower 64 bit of the 128 bit integer
 */
void print_int128_as_hex(__int128 x)
{
    __uint64_t high = (x >> 64);
    printf("HIGH (64 bit) = 0x%" PRIx64 " ", high);
    __uint64_t low = (__uint64_t)x;
    printf("LOW (64 bit) = 0x%" PRIx64 "\n", low);
}

/**
 * print __int128 as binary with a line break after (if you don't want the line break, just delete the putchar('\n') line)
 */
void print_int128_bin(__int128 x)
{
    print_int128_bin_aux(x);
    putchar('\n');
}
/**
 * print __int128 with one line break after
 */
void print_int128n(__int128 x)
{
    print_int128_aux(x);
    putchar('\n');
}
/**
 * print __int128 with one space after
 */
void print_int128s(__int128 x)
{
    print_int128_aux(x);
    putchar(' ');
}

// read function

// we get the general idea from strtol implementation, but rewrite it to 128 bit integer implementation
//https://code.woboq.org/gcc/libiberty/strtol.c.html

/*
 * Convert a string to a 128 bit integer with useful error handling.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */

__int128
strtoi128(const char *nptr, char **endptr, register int base, __int128 *output)
{
    register const char *s = nptr;
    __int128 acc;
    register int c;
    register int neg = 0;
    __int128 any;

    // we skip all spaces
    do
    {
        c = *s++;
    } while (isspace(c));
    // we look whether a '0b' is in front of the number, if so, we change the base to 2
    if (c == '0' && *s == 'b')
    {
        base = 2;
        c = *s++;
        c = *s++;
    }
    // we look whether a '0x' is in front of the number, if so, we change the base to 16 (hexadecimal)
    if (c == '0' && *s == 'x')
    {
        base = 16;
        c = *s++;
        c = *s++;
    }
    // we look whether a '-' or '~' indicates that our number shall be interpreted negative
    if (c == '~' || c == '-')
    {
        neg = 1;
        c = *s++;
    }
    // our number is positive and we just skip the sign
    else if (c == '+')
    {
        c = *s++;
    }
    // if no explicit base is given, we look whether the number has a leading 0 which indicates base 8, or we assume base 10 per default
    if (base == 0)
        base = c == '0' ? 8 : 10;
    int i = 0;

    // here we go through the number and cut off the number as soon as we get an invalid character
    for (acc = 0, any = 0;; c = *s++, i++)
    {
        if (isdigit(c))
        {
            c -= '0';
        }
        else if (isalpha(c))
        {
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        }
        else
        {
            //printf("we break because of invalid character (character in ascii, so 0 = nullbyte). %i\n", c);
            break;
        }
        if (c >= base)
        {
            //printf("we break because a number to high for the base.");
            break;
        }
        else
        {
            __int128 before = acc;
            any = 1;
            acc *= base;
            acc += c;
            if ((unsigned __int128)acc < (unsigned __int128)before)
            {
                any = -1;
            }
        }
    }
    // we do error handling here, if the number was too large for 128 bit
    if (i > 128 || any < 0)
    {
        acc = -1;
        errno = ERANGE;
        //printf("You input a number bigger than 128 bit, this might (and most certainly will) lead to wrong results.\n");
    }
    // account for the '-' or '~'
    else if (neg)
    {
        acc = -acc;
    }
    // further error handling
    if (endptr != 0)
    {
        *endptr = (char *)(any ? s - 1 : nptr);
    }
    // error handling if the given pointer is null
    if (output == NULL)
    {
        return acc;
    }
    else
    {
        *output = acc;
    }
    return acc;
}
