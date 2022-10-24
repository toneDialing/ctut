#include <stdio.h>

// Prints longest line of input

#define MAXLINE 1000    //Max input line size

int getinputline(char line[], int maxline); //The book uses "getline", but this is now a real function in C so shouldn't be used as a custom function name
void copy(char to[], char from[]);

int main(void)
{
    int len;                //current line length
    int max;                //max length seen so far
    char line[MAXLINE];     //current input line
    char longest[MAXLINE];  //longest line saved here

    max = 0;
    while((len = getinputline(line, MAXLINE)) > 0)
    {
        if(len>max)
        {
            max = len;
            copy(longest, line);
        }
    }
    if(max>0)
    {
        printf("%s", longest);
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

void copy(char to[], char from[]) //Copy "from" into "to", and assume "to" is big enough
{
    int i;

    i = 0;
    while((to[i] = from[i]) != '\0')
    {
        i++;
    }
}