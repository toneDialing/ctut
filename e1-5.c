#include <stdio.h>

// Copies input to output

int main(void)
{
    int c;

    while( (c=getchar()) != EOF)
    {
        putchar(c);
    }
}