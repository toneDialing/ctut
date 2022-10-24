#include <stdio.h>

// Prints a horizontal histogram of word length in input
// Here, a "word" is any string of characters unbroken by ' ', '\t', or '\n'

#define IN 1    //Inside a word
#define OUT 0   //Outside a word
#define MAX 50  //Maximum number of words permitted in input

int main(void)
{
    int c, l, w, state;
    int wordlength[MAX];

    state = OUT;    //Set all values = 0
    w = l = 0;
    for(int i=0; i<MAX; i++)
    {
        wordlength[i] = 0;
    }

    while((c=getchar()) != EOF) //Stores length of ith word in wordlength[i]
    {
        if(c==' ' || c=='\n' || c=='\t')
        {
            if(state == IN)
            {
                wordlength[w] = l;
                w++;
                l = 0;
            }
            state = OUT;
        }
        else if(state == OUT)
        {
            state = IN;
            l++;
        }
        else l++;
    }
    
    for(int i=0; i<w; i++) //Prints hashes to represent word length, one hash row per line
    {
        for(int j=0; j<wordlength[i]; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}