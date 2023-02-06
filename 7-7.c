#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* Modify the pattern finding program of Chapter 5 to take its input from a set of named files or,
    if no files are named as arguments, from the standard input. Should the file name be printed
    when a matching line is found? */

/* File name is printed when matching line is found. Used get_line() for searching standard input
    in order to keep it similar to the example from Chapter 5, even though it's not necessary. */

int get_line(char *, int);

int main(int argc, char *argv[])
{
    FILE *fp;
    char line[MAXLINE];
    int found = 0;

    if(argc==1)
    {
        printf("Usage: ./7-7 [pattern] [opt. file names]\n");
        return 0;
    }

    char *pattern = *++argv;
    if(argc==2)
    {
        while(get_line(line, MAXLINE)>0)
        {
            if(strstr(line, pattern)!=NULL)
            {
                printf("%s", line);
                found++;
            }
        }
        printf("Total matches found: %d\n", found);
        return 0;
    }

    while(--argc>1)
    {
        if((fp=fopen(*++argv, "r"))==NULL)
        {
            printf("error: unable to open file %s\n", *argv);
            return 0;
        }
        while(fgets(line, MAXLINE, fp)!=NULL)
        {
            if(strstr(line, pattern)!=NULL)
            {
                printf("%s:\n\t%s\n", *argv, line); /* potentially redundant '\n' added again */
                found++;
            }
        }
        fclose(fp);
    }
    printf("Total matches found: %d\n", found);
    return 0;
}

/* get_line: read a line, return length */
int get_line(char *line, int max)
{
    if(fgets(line, max, stdin)==NULL)
        return 0;
    else
        return strlen(line);
}