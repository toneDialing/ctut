#include <stdio.h>
#define MAXLINE 1000 //Maximum input line length

int readline(char line[], int max);
int str_rindex(char source[], char searchfor[]);

char pattern[] = "ould"; //Pattern to search for

/* Finds all lines of input matching a designated pattern, and prints them */

/* Find all lines matching pattern */
int main(void)
{
    char line[MAXLINE];
    int found = 0;
    int pos;

    while(readline(line, MAXLINE) > 0)
    {
        if((pos = str_rindex(line, pattern)) >= 0)
        {
            printf("%s%d\n", line, pos);
            found++;
        }
    }
    return found;
}

/* Get line into s, return length */
int readline(char s[], int lim)
{
    int c, i;
    i = 0;

    while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }
    if(c=='\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';

    return i;
}

/* Return rightmost index of t in s, -1 if none */
int str_rindex(char s[], char t[])
{
    int i, j, k;
    int rightmost = -1;

    for(i=0; s[i]!='\0'; i++)
    {
        for(j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
        {
            ;
        }
        if(k>0 && t[k]=='\0')
        {
            rightmost = i;
        }
    }
    return rightmost;
}