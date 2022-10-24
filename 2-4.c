#include <stdio.h>
#include <stdlib.h>

#define MAX 500

/* Gets two strings from user, runs squeeze(), and prints result */

void squeeze(char *s1, char *s2); //Deletes each character in s1 that matches any character in s2

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

    squeeze(s1, s2);
    printf("New string: %s\n", s1);

    free(s1);
    free(s2);
    return 0;
}

void squeeze(char *s1, char *s2) //Processing time of O(n^2), could probably be faster if I used a hash table
{
    int i, j, k, match;
    match = k = 0;

    for(i=0; s1[i] != '\0'; i++)
    {
        for(j=0; s2[j] != '\0'; j++)
        {
            if(s1[i]==s2[j])
            {
                match++;
            }
        }
        if(match==0)
        {
            s1[k++] = s1[i];
        }
        match = 0;
    }
    s1[k] = '\0';
}