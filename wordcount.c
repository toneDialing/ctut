#include <stdio.h>

// Counts lines, words, and characters in input

#define IN 1    //state of being inside a word
#define OUT 0   //state of being outside a word

int main(void)
{
    int c, state;
    double cc, wc, lc;

    cc = wc = lc = 0;
    state = OUT;

    while((c=getchar()) != EOF)
    {
        cc++;
        if(c=='\n')
        {
            lc++; /* If text is written without a terminating '\n' then this will undercount,
                    but it seems you need a '\n' immediately preceding to execute EOF anyway
                    so in practice it's fine */
        }
        if(c=='\n' || c=='\t' || c==' ')
        {
            state = OUT;
        }
        else if(state==OUT)
        {
            state = IN;
            wc++;
        }
    }
    printf("Characters: %.0f\nWords: %.0f\nLines: %.0f\n", cc, wc, lc);
}