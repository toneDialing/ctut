#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000  /* max number of lines to be read */
#define STORAGE_SIZE 100000  /* storage space allocated for all lines */
#define DEFAULT_LAST_LINES 10   /* default number of previous lines to be printed */

char *lineptr[MAX_LINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char storage[]);
void writelines(char *lineptr[], int nlines);

/* Prints last n lines of input. By default n = 10, but can be set with -n option in command line */
int main(int argc, char *argv[])
{
    int nlines; /* number of input lines read */
    int n = DEFAULT_LAST_LINES;
    char line_storage[STORAGE_SIZE];
    char **p = lineptr; /* I'm not sure why I can't increment lineptr directly.
                        Perhaps because it's declared as an array rather than a pointer.
                        When it gets passed through a function, as in writelines() in 5-7.c,
                        then it can be incremented, but of course at that point it's been passed
                        to the function as a pointer. */

    if(argc>1)
    {
        if((*++argv)[0] == '-')
        {
            n = atoi(*argv);
            n = -n;
        }

        if(n<1) /* If n is invalid, return n to default */
        {
            n = DEFAULT_LAST_LINES;
        }
    }

    if((nlines = readlines(lineptr, MAX_LINES, line_storage)) >= 0)
        {
            while(nlines > n)
            {
                p++;
                nlines--;
            }

            while(nlines-- > 0)
            {
                printf("%s\n", *p++);
            }
        }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */
int get_line(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char storage[])
{
    int len, nlines;
    char *p, line[MAXLEN];
    p = storage;

    nlines = 0;
    while((len = get_line(line, MAXLEN)) > 0)
    {
        if(nlines >= maxlines || ((storage + STORAGE_SIZE - p) < len))
        {
            return -1;
        }
        else
        {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}

/* get_line: get line into s, return length */
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