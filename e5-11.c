#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void q_sort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int str_cmp(char *s, char *t);

/* Sort input lines */
/* Assumes valid input */
int main(int argc, char *argv[])
{
    int nlines;         /* number of input lines read */
    int numeric = 0;    /* 1 if numeric sort, 0 if lexicographic sort */

    if(argc>1 && str_cmp(argv[1], "-n")==0)
    {
        numeric = 1;
    }

    if((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        q_sort((void **) lineptr, 0, nlines-1, (int (*)(void *, void *))(numeric ? numcmp : str_cmp));
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("input too big to sort\n");
        return 1;
    }
}

/* q_sort: sort v[left], ..., v[right] into increasing order */
void q_sort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if(left>=right)     /* do nothing if array contains fewer than two elements */
    {
        return;
    }

    swap(v, left, (left+right)/2);
    last = left;
    for(i = left+1; i<=right; i++)
    {
        if((*comp)(v[i], v[left]) < 0)
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    q_sort(v, left, last-1, comp);
    q_sort(v, last+1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if(v1<v2)
    {
        return -1;
    }
    else if(v1>v2)
    {
        return 1;
    }
    else return 0;
}

/* str_cmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int str_cmp(char *s, char *t)
{
    for(; *s == *t; s++, t++)
    {
        if(*s == '\0')
        {
            return 0;
        }
    }
    return *s - *t;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000 /* max length of any input line */
int get_line(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;

    while((len = get_line(line, MAXLEN)) > 0)
    {
        if(nlines >= maxlines || (p=alloc(len)) == NULL)
        {
            return -1;
        }
        else
        {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for(i=0; i<nlines; i++)
    {
        printf("%s\n", lineptr[i]);
    }
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

#define ALLOCSIZE 100000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
    if(allocbuf + ALLOCSIZE - allocp >= n) /* it fits */
    {
        allocp += n;
        return allocp - n; /* old p */
    }
    else return NULL; /* not enough room */
}