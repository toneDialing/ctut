#include <stdio.h>

// Copy input to output, replacing tabs, backspaces, and backslashes

int main(void)
{
    int c;

    while((c=getchar()) != EOF)
    {
        if(c=='\t')
        {
            printf("\\t");
        }
        else if(c=='\b')
        {
            printf("\b");
        }
        else if(c=='\\')
        {
            printf("\\\\");
        }
        else
        {
            putchar(c);
        }
    }
}