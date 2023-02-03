#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

/* Write a program that will print arbitrary input in a sensible way. As a minimum, it should print
    non-graphic characters in octal or hexadecimal according to local custom, and break long text lines. */

/* This program currently breaks long text lines but doesn't handle non-graphic characters
    because unfortunately I don't yet understand how those work. */

int main(void)
{
    int c;
    int line_length = 0;

    while((c=getchar())!=EOF)
    {
        if(c=='\n')
        {
            putchar(c);
            line_length = 0;
        }
        else if(line_length>=MAX_LINE_LENGTH)
        {
            putchar('\n');
            putchar(c);
            line_length = 1;
        }
        else
        {
            putchar(c);
            line_length++;
        }
    }
    putchar('\n');

    return 0;
}