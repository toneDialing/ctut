#include <stdio.h>
#include <ctype.h>

/* Create a reverse Polish calculator that functions entirely within the command line */
/* Don't need to store variables or do advanced operations */

/* Pull code from previous Polish calculator */
/* Need push() and pop() from 4-10.c, don't need readline(), need atof() and much of 4-10's main() */

void push(double);
double pop(void);

int main(int argc, char *argv[])
{
    if(argc<4)
    {
        printf("Insufficient operands\n");
        return 0;
    }
}

#define MAXVAL 100

int stack_position = 0;
double stack[MAXVAL];

void push(double f)
{

}

double pop(void)
{

}