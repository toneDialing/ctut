#include <stdio.h>

//Counts the frequency of q, x, and z, and prints the result as a histogram.

int main(void)
{
    int c;
    int q, x, z;
    q = x = z = 0;

    while((c=getchar()) != EOF)
    {
        if(c=='Q' || c=='q')
        {
            q++;
        }
        else if(c=='X' || c=='x')
        {
            x++;
        }
        else if(c=='Z' || c=='z')
        {
            z++;
        }
    }
    printf("Q's: ");
    for(int i=0; i<q; i++)
    {
        printf("#");
    }
    printf("\nX's: ");
    for(int i=0; i<x; i++)
    {
        printf("#");
    }
    printf("\nZ's: ");
    for(int i=0; i<z; i++)
    {
        printf("#");
    }
    printf("\n");
}