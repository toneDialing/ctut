#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

/* Rewrites get_line() with pointers instead of array indexing */
int get_line(char *s, int lim);

int main(void)
{
    char *s = malloc(MAXLINE*sizeof(char));

    printf("Enter string: ");
    get_line(s, MAXLINE);

    printf("Your string: %s", s);

    free(s);
    return 0;
}

/* Get line into s, return length */
int get_line(char *s, int lim)
{
    int c;
    char *start = s;

    while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
    {
        *s++ = c;
    }
    if(c=='\n')
    {
        *s++ = c;
    }
    *s = '\0';
    return s - start;
}