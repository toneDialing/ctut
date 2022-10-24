#include <stdio.h>
#include <stdlib.h>

#define MAX 500

/* Gets two strings from user, runs matchpos(), and prints result */

int matchpos(char *s1, char *s2); //Returns position of first character in s1 to match any character in s2
//Position count starts at 1, not 0

int main(void)
{
    int c, i;
    char *s1 = malloc(MAX*sizeof(char));
    char *s2 = malloc(MAX*sizeof(char));
    i = 0;

    printf("String 1: ");
    while((c=getchar()) != '\n')
    {
        s1[i++] = c;
    }
    s1[i] = '\0';
    i = 0;

    printf("String 2: ");
    while((c=getchar()) != '\n')
    {
        s2[i++] = c;
    }
    s2[i] = '\0';

    int n = matchpos(s1, s2);
    if(n==-1)
    {
        printf("No match. Sorry! :(\n");
    }
    else
    {
        printf("There is a match at position %d\n", n);
    }

    free(s1);
    free(s2);
    return 0;
}

int matchpos(char *s1, char *s2)
{
    int i, j;

    for(i=0; s1[i] != '\0'; i++)
    {
        for(j=0; s2[j] != '\0'; j++)
        {
            if(s1[i]==s2[j])
            {
                return i+1;
            }
        }
    }
    return -1;
}