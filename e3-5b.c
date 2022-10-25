#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

/* Reverses a given input string */

void reverse(char *s);

int main(void)
{
    int c, i;
    char *s = malloc(MAX*sizeof(char));
    i = 0;

    printf("String: ");
    while((c=getchar())!='\n' && c!=EOF)
    {
        s[i++] = c;
    }
    s[i] = '\0';

    reverse(s);

    printf("New string: %s\n", s);

    free(s);
    return 0;
}

void reverse(char *s)
{
    int c, i, j;

    for(i=0, j=strlen(s)-1; i<j; i++, j--)
    {
        c=s[i], s[i]=s[j], s[j]=c;
    }
}