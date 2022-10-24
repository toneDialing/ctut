#include <stdio.h>

// Counts number of lines in input by counting '\n'

int main(void)
{
    int c, nl;

    nl=0;
    while( (c=getchar()) != EOF)
    {
        if(c=='\n')
        {
            nl++;
        }
    }
    printf("%d\n", nl);
}