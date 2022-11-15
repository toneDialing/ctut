#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

void string_concat(char *s, char *t);
/* Concatenate t to end of s; s must be big enough */
/* Assumes concatenated string is smaller than MAX_LENGTH */

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

    string_concat(s, t);
    printf("New concatenated string: %s\n", s);

    free(s);
    free(t);
    return 0;
}

void string_concat(char *s, char *t)
{
    while(*s++)
        ;
    s--;
    while((*s++ = *t++))
        ;
}