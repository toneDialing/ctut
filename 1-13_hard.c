#include <stdio.h>

// Prints a vertical histogram of word length in input
// Here, a "word" is any string of letters unbroken by any other characters

#define IN 1    //Inside a word
#define OUT 0   //Outside a word
#define MAX 150  //Maximum number of words permitted in input

int main(void)
{
    int c, l, w, state, longest;
    int wordlength[MAX];

    state = OUT;    //Set all values = 0
    w = l = longest = 0;
    for(int i=0; i<MAX; i++)
    {
        wordlength[i] = 0;
    }

    while((c=getchar()) != EOF) //Stores length of ith word in wordlength[i]
    {
        if(c<'A' || c>'z' || c>'Z' && c<'a')
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

    for(int i=0, j=0; i<w; i++) //Stores longest word length in "longest"
    {
        j = wordlength[i];
        if(j>longest)
        {
            longest = j;
        }
    }

    for(int k = longest; k>0; k--) //Prints vertical histogram of word length using hashes
    {
        for(int i=0; i<w; i++)
        {
            if(wordlength[i]>=k)
            {
                printf("#");
            }
            else printf(" ");
        }
        printf("\n");
    }
}