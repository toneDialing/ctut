#include <stdio.h>
#include <stdlib.h>

#define MAX 500

/* Replaces all '\n' & '\t' escape sequences in an input string with the real characters */

void escape_rev(char *s, char *t);

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

    escape_rev(s, t);
    printf("New string: %s\n", t);
    /* The '\n' is somewhat redundant given my limited knowledge of how to induce EOF */

    free(s);
    free(t);
    return 0;
}

void escape_rev(char *s, char *t)
{
    int j = 0;
    for(int i = 0; s[i]!='\0'; i++)
    {
        switch(s[i])
        {
            case '\\':
                switch(s[i+1])
                {
                    case 'n':
                        t[j++] = '\n';
                        i++;
                        break;
                    case 't':
                        t[j++] = '\t';
                        i++;
                        break;
                    default:
                        t[j++] = '\\';
                        break;
                }
                break;
            default:
                t[j++] = s[i];
                break;
        }
    }
    t[j] = '\0';
}