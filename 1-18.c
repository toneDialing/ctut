#include <stdio.h>

//Removes trailing blanks and tabs from input lines

#define MAXLINE 1000

int getinputline(char line[], int maxline);
void cleancopy(char to[], char from[]);

int main(void)
{
    int len;
    char line[MAXLINE];
    char cleanline[MAXLINE];

    while((len = getinputline(line, MAXLINE)) > 0)
    {
        cleancopy(cleanline, line);
        printf("%s", cleanline);
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

void cleancopy(char to[], char from[]) //Copy but remove trailing blanks/tabs
{
    int i, j;

    i = 0;
    while(from[i] != '\0')
    {
        if(from[i] == ' ' || from[i] == '\t') //Checks for trailing blanks and deletes them, then breaks loop
        {
            for(j=i; from[j] == ' ' || from[j] == '\t'; j++)
            {
                ;
            }
            if(from[j] == '\n')
            {
                to[i]=from[j];
                to[i+1] = '\0';
                break;
            }
        }
        else if(from[i] == '\n') //In absense of trailing blanks, simply break loop
        {
            to[i]=from[i];
            to[i+1] = '\0';
            break;
        }
        to[i] = from[i];
        i++;
    }
}