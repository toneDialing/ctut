#include <stdio.h>
#include <stdlib.h>

#define MAX 500

/* Gets a string from user and returns it in all lower-case. Assumes ASCII standard */

int lower(int c);

int main(void)
{
    int c, i;
    char *s = malloc(MAX*sizeof(char));
    i = 0;

    printf("Please enter a string: ");
    while((c=getchar()) != '\n' && c != EOF)
    {
        s[i++] = c;
    }
    s[i] = '\0';

    for(i=0; s[i]!='\0'; i++)
    {
        s[i] = lower(s[i]);
    }

    if(c==EOF) printf("\nError: EOF\n");
    else printf("Lower-case string: %s\n", s);

    free(s);
    return 0;
}

int lower(int c)
{
    return (c>='A' && c<='Z') ? c+'a'-'A' : c;
}