#include <stdio.h>

//Prints input one word per line

#define IN 1    //State of being inside a word
#define OUT 0   //State of being outside a word

int main(void)
{
    int c, state;

    state = OUT;

    while((c=getchar()) != EOF)
    {
        if(c=='\n' || c=='\t' || c==' ')
        {
            state = OUT;
        }
        else if(state==OUT)
        {
            state = IN;
            do
            {
                putchar(c);
                c = getchar();
            }
            while(c != '\n' && c != '\t' && c != ' ');
            state = OUT;
            putchar('\n');
        }
    }
}