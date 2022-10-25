#include <stdio.h>
#include <stdlib.h>

#define MAX 500

/* Replaces all tabs and newlines in an input string with their literal character representations */

void escape(char *s, char *t);

int main(void)
{
    int c, i;
    char *s = malloc(MAX*sizeof(char));
    char *t = malloc(MAX*sizeof(char));
    i = 0;

    printf("Enter string: ");
    while((c=getchar())!=EOF)
    {
        s[i++] = c;
    }
    s[i] = '\0';

    escape(s, t);
    printf("New string: %s\n", t);

    free(s);
    free(t);
    return 0;
}

void escape(char *s, char *t)
{
    int j = 0;
    for(int i = 0; s[i]!='\0'; i++)
    {
        switch(s[i])
        {
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            default:
                t[j++] = s[i];
                break;
        }
    }
    t[j] = '\0';
}