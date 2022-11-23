#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int get_line(char *line, int max);

/* Print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0; // line number; this is how K&R named it
    int c, except = 0, number = 0, found = 0;

    while(--argc>0 && (*++argv)[0] == '-')
    /* Note that [] binds tighter than * or ++, and there is thus a difference between
    the syntax of argv in these two while loops */
    {
        while((c = *++argv[0])) // assignment is placed in while loop to avoid setting c = '\0'
        /* Double parentheses are necessary to avoid warning upon compilation,
        as while() expects a boolean expression */
        {
            switch(c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("Illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
        }
    }
    if(argc!=1)
    {
        printf("Usage: e5-10c -x -n pattern\n");
    }
    else
    {
        while(get_line(line, MAXLINE) > 0)
        {
            lineno++;
            if((strstr(line, *argv) != NULL) != except)
            {
                if(number)
                {
                    printf("%ld:", lineno);
                }
                printf("%s", line);
                found++;
            }
        }
    }
    return found;
}

int get_line(char *line, int max)
{
    int c;
    char *start = line;

    while(--max > 0 && (c=getchar()) != EOF && c != '\n')
    {
        *line++ = c;
    }
    if(c=='\n')
    {
        *line++ = c;
    }
    *line = '\0';
    return line - start;
}