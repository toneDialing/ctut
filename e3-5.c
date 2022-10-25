#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 500

/* Converts a string to an int, assuming valid input and returning 0 otherwise */

int stringtoint(char *s);

int main(void)
{
    int c, i, n;
    char *s = malloc(MAX*sizeof(char));
    i = 0;

    printf("String: ");
    while((c=getchar())!='\n' && c!=EOF)
    {
        s[i++] = c;
    }
    s[i] = '\0';

    n = stringtoint(s);
    printf("Integer: %d\n", n);

    free(s);
    return 0;
}

int stringtoint(char *s)
{
    int i, n, sign;

    for(i=0; isspace(s[i]); i++)
    {
        ;
    }

    sign = (s[i]=='-') ? -1 : 1;
    if(s[i]=='+' || s[i]=='-')
    {
        i++;
    }

    for(n=0; isdigit(s[i]); i++)
    {
        n = 10*n + (s[i]-'0');
    }

    return sign*n;
}