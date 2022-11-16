#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define STORAGE_SIZE 100000 /* size of available space */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char storage[]);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* Sorts input lines alphabetically. End input by entering EOF */
/* Modified readlines() to avoid using alloc() */

/* sort input lines */
int main(void)
{
    int nlines; /* number of input lines read */
    char line_storage[STORAGE_SIZE];

    if((nlines = readlines(lineptr, MAXLINES, line_storage)) >= 0)
        {
            qsort(lineptr, 0, nlines-1);
            writelines(lineptr, nlines);
            return 0;
        }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */
int get_line(char *, int);
char *alloc(int);

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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while(nlines-- > 0)
    {
        printf("%s\n", *lineptr++);
    }
}

/* qsort: sort v[left], ..., v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if(left >= right) /* do nothing if array contains fewer than two elements */
    {
        return;
    }

    swap(v, left, (left+right)/2);
    last = left;
    for(i = left+1; i<=right; i++)
    {
        if(strcmp(v[i], v[left]) < 0 )
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);

    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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