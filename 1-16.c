#include <stdio.h>

// Prints input lines and displays their character length

#define MAXLINE 1000    //Max input line size

int getinputline(char line[], int maxline); //The book uses "getline", but this is now a real function in C so shouldn't be used as a custom function name

int main(void)
{
    int len;                //current line length
    char line[MAXLINE];     //current input line

    while((len = getinputline(line, MAXLINE)) > 0)
    {
        printf("Length: %d || %s", len, line);
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