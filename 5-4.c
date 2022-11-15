#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

int string_end(char *s, char *t);
/* Returns 1 if string t occurs at end of string s, and 0 otherwise */

int main(void)
{
    char *s = malloc(MAX_LENGTH*sizeof(char));
    char *t = malloc(MAX_LENGTH*sizeof(char));
    int c, i;
    i = 0;

    printf("Enter first string: ");
    while((c=getchar())!='\n' && c!=EOF && i<(MAX_LENGTH-1))
    {
        s[i++] = c;
    }
    s[i] = '\0';
    i = 0;

    printf("Enter second string: ");
    while((c=getchar())!='\n' && c!=EOF && i<(MAX_LENGTH-1))
    {
        t[i++] = c;
    }
    t[i] = '\0';

    int n = string_end(s, t);
    printf("%d\n", n);

    free(s);
    free(t);
    return 0;
}

int string_end(char *s, char *t)
{
    int i = strlen(t);
    while(*s++)
        ;
    s -= (i+1);
    while(*t)
    {
        if(*s++ == *t++)
            ;
        else return 0;
    }
    return 1;
}