#include <stdio.h>

// Counts digits, white space, and other characters

int main(void)
{
    int c, i, white, other;
    int ndigit[10];

    white = other = 0;
    for(i=0; i<10; i++)
    {
        ndigit[i]=0;
    }

    while((c=getchar()) != EOF)
    {
        if(c >= '0' && c <= '9')
        {
            ndigit[c-'0']++;
        }
        else if(c == ' ' || c == '\n' || c == '\t')
        {
            white++;
        }
        else other++;
    }

    printf("Digits:");
    for(i=0; i<10; i++)
    {
        printf(" %d: %d", i, ndigit[i]);
        if(i<9) printf(",");
    }
    printf("\n");
    printf("White space: %d\n", white);
    printf("Other characters: %d\n", other);
}