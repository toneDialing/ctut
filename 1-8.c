#include <stdio.h>

// Counts blanks, tabs, and newlines in input text

int main(void)
{
    int c, nl, b, t;

    nl = b = t = 0;
    while ((c=getchar()) != EOF)
    {
        if(c=='\n')
        {
            nl++;
        }
        else if(c==' ')
        {
            b++;
        }
        else if(c=='\t')
        {
            t++;
        }
    }
    printf("Blanks: %d\nTabs: %d\nNewlines: %d\n", b, t, nl);
}