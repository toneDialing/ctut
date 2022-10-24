#include <stdio.h>

//Reverses input one line at a time

#define MAXLINE 1000

int getinputline(char line[], int maxline);
void reverse(char r[], char s[], int len);

int main(void)
{
    int len;
    char line[MAXLINE];
    char r[MAXLINE];

    while((len = getinputline(line, MAXLINE)) > 0)
    {
        reverse(r, line, len);
        printf("%s", r);
    }
    return 0;
}

void reverse(char r[], char s[], int len) //Copies s into r in reverse order given the length of s
{
    int i = 0;

    for(int l = len; l>1; l--)
    {
        r[i] = s[l-2];
        i++;
    }
    r[i] = '\n';
    r[i+1] = '\0';
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