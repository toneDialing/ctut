#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 500

void expand(char *s, char *t);

int main(void)
{
    int c, i;
    char *s = malloc(MAX*sizeof(char));
    char *t = malloc(MAX*sizeof(char));
    i = 0;

    printf("Enter string: ");
    while((c=getchar())!='\n' && c!=EOF)
    {
        s[i++] = c;
    }
    s[i] = '\0';

    free(s);
    free(t);
    return 0;
}

void expand(char *s, char *t)
{
    int j = 0;
    for(int i=0; s[i]!='\0'; i++)
    {
        switch (s[i])
        {
            case '-':
                if(isalnum(s[i-1]))
                {
                    
                }
            default:
                t[j++] = s[i];
                break;                
        }
    }
}
