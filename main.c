#include "int128_lib.h"
#include <stdio.h>
#include <errno.h> // for errno

int main(int argc, char **argv)
{
    // reading an __int128 number
    char number[129];
    printf("Please input your number:");
    fgets(number, sizeof(number), stdin);
    __int128 intputInteger128;
    char *p;
    errno = 0;
    // the third argument is the base the number is interpreted as, now it's interpreted as a decimal number
    strtoi128(argv[1], &p, 10, &intputInteger128);

    // error checks: the string does not represent an integer
    if (errno != 0 || *p != '\0')
    {
        fprintf(stderr, "You entered something invalid but not a 128 integer");
        return 1;
    }
    else
    {
        // No error
        // we print the number
        print_int128n(intputInteger128);
    }
    return 0;
}
