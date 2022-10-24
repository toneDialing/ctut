#include <stdio.h>

// Copy input to output, replacing multiple spaces with single spaces

int main(void)
{
    int c;

    while( (c=getchar()) != EOF)
    {
        if(c==' ')
        {
            putchar(c);
            while((c=getchar()) == ' ')
            {
                ;
            }
        }
        putchar(c);
    }
}