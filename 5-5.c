#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

void string_ncopy(char *s, char *t, int n);
void string_nconcat(char *s, char *t, int n);
int string_ncomp(char *s, char *t, int n);

/* Each function performs its usual operation on at most n characters */

int main(void)
{
    char *s = malloc(MAX_LENGTH*sizeof(char));
    char *t = malloc(MAX_LENGTH*sizeof(char));
    int c, i, n;
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

    printf("Enter max chars: ");
    scanf("%d", &n);
    while((c=getchar())!='\n') //Forces getchar() to skip over scanned input line
        ;

    printf("Enter 'a' for copy, 'b' for concatenate, or 'c' for compare: ");
    if((c=getchar())=='a')
    {
        string_ncopy(s, t, n);
        printf("Copied string: %s\n", s);
    }
    else if(c=='b')
    {
        string_nconcat(s, t, n);
        printf("Concatenated string: %s\n", s);
    }
    else if(c=='c')
    {
        int comp = string_ncomp(s, t, n);
        printf("Comparison result: %d\n", comp);
    }
    else printf("Invalid input\n"); //Extra chars following a/b/c do not register as invalid input

    free(s);
    free(t);
    return 0;
}

/* As written, string_ncopy() replaces s with t if strlen(t) is less than n,
but otherwise pastes t into s if strlen(t) is greater than or equal to n.
I don't know what K&R intended for me to do so I'm just leaving it as is. */
void string_ncopy(char *s, char *t, int n)
{
    int i = 0;
    while(i++<n && (*s++ = *t++))
        ;
}

void string_nconcat(char *s, char *t, int n)
{
    int i = 0;
    while(*s++)
        ;
    s--;
    while(i++<n && (*s++ = *t++))
        ;
}

int string_ncomp(char *s, char *t, int n)
{
    int i;
    for(i = 0; *s == *t && i<n; s++, t++, i++)
    {
        if(*s=='\0')
        {
            return 0;
        }
    }
    if(i>=n)
    {
        s--;
        t--;
    }
    return *s - *t;
}