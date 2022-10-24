#include <stdio.h>

//Prints all input lines longer than 80 characters

#define MAXLINE 1000 //Max input line size

int getinputline(char line[], int maxline);

int main(void)
{
    int len;
    char line[MAXLINE];

    while((len = getinputline(line, MAXLINE)) > 0)
    {
        if(len>80)
        {
            printf("%s", line);
        }
    }
    return 0;
}

int getinputline(char s[], int lim) //Read a line into s, return length
{
    int c, i;

    for(i=0; i<(lim-1) && (c=getchar())!=EOF && c!='\n'; i++)
    {
        s[i] = c;
    }
    if(c=='\n')
    {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}