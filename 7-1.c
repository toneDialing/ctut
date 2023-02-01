#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Write a program that converts upper case to lower or lower case to upper, depending on the name
    it is invoked with, as found in argv[0] */

/* This could also have been written using a pointer to a function, but this seems clear enough */

int main(int argc, char *argv[])
{
    int c;

    if(argc!=2)
    {
        printf("command line error: type \"lower\" or \"upper\"\n");
        return 0;
    }

    if(strcmp(argv[1], "lower")==0)
    {
        while((c=getchar())!=EOF)
        {
            putchar(tolower(c));
        }
    }
    else if(strcmp(argv[1], "upper")==0)
    {
        while((c=getchar())!=EOF)
        {
            putchar(toupper(c));
        }
    }
    else printf("command line error: type \"lower\" or \"upper\"\n");

    return 0;
}