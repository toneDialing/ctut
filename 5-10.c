#include <stdio.h>
#include <ctype.h>

/* Create a reverse Polish calculator that functions entirely within the command line */
/* Don't need to store variables or do advanced operations */

/* Pull code from previous Polish calculator */
/* Need push() and pop() from 4-10.c, don't need readline(), need atof() and much of 4-10's main() */
int main(int argc, char *argv[])
{
    if(argc<4)
    {
        printf("Insufficient operands\n");
        return 0;
    }
}