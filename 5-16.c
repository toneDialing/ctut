#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000       /* max #lines to be sorted */
#define MAXLEN 1000         /* max length of any input line */
char *lineptr[MAXLINES];    /* pointers to text lines */
int caseless;               /* 1 if case is ignored, 0 if not */
int alphanum_only;          /* 1 if only alphanum chars are to be evaluated, 0 if not */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void q_sort(void *lineptr[], int left, int right, int reverse, int (*comp)(void *, void *));
int num_cmp(char *, char *);
int str_cmp(char *s, char *t);
void str_trim(char *, char *);
void str_cpy(char *, char *);

/* Sort input lines */
/* Assumes valid input -- note that num_cmp() always returns 0 when comparing non-digits,
    so sorting words with num_cmp() creates nonsense as qsort() only executes certain swaps. */
/* Add "-r" command-line option, which sorts in reverse order. Reversal is indicated through
    an additional parameter to q_sort() */
/* Add "-f" command-line option, which treats upper- and lowercase as equivalent. Achieved
    through use of static ext. variable caseless. Perhaps not the intended solution but it
    seemed to be the simplest method. */
/* Add "-d" command-line option, which only makes comparisons on alphanumeric chars and spaces */
int main(int argc, char *argv[])
{
    int nlines;         /* number of input lines read */
    int numeric = 0;    /* 1 if numeric sort, 0 if lexicographic sort */
    int reverse = 0;    /* 1 if reverse sort, 0 if regular sort */
    int c;

    while(--argc > 0 && (*++argv)[0] == '-')
    {
        while((c = *++argv[0]))
        {
            switch(c)
            {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                case 'f':
                    caseless = 1;
                    break;
                case 'd':
                    alphanum_only = 1;
                    break;
                default:
                    break;
            }
        }
    }

    if((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        q_sort((void **) lineptr, 0, nlines-1, reverse,
            (int (*)(void *, void *))(numeric ? num_cmp : str_cmp));
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
void q_sort(void *v[], int left, int right, int reverse, int (*comp)(void *, void *))
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
        if(reverse)
        {
            if((*comp)(v[i], v[left]) > 0)
            {
                swap(v, ++last, i);
            }
        }
        else
        {
            if((*comp)(v[i], v[left]) < 0)
            {
                swap(v, ++last, i);
            }
        }
    }
    swap(v, left, last);
    q_sort(v, left, last-1, reverse, comp);
    q_sort(v, last+1, right, reverse, comp);
}

/* num_cmp: compare s1 and s2 numerically */
int num_cmp(char *s1, char *s2)
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
    int result;
    char *s1 = malloc(MAXLEN*sizeof(char));
    char *t1 = malloc(MAXLEN*sizeof(char));
    char *s_alloc = s1; // these pointers don't move,
    char *t_alloc = t1; // so the strings can be freed from their start later on
    if(alphanum_only)
    {
        str_trim(s1, s);
        str_trim(t1, t);
    }
    else
    {
        str_cpy(s1, s);
        str_cpy(t1, t);
    }
    if(caseless)
    {
        for(; tolower(*s1) == tolower(*t1); s1++, t1++)
        {
            if(*s1 == '\0')
            {
                free(s_alloc);
                free(t_alloc);
                return 0;
            }
        }
        result = tolower(*s1) - tolower(*t1);
        free(s_alloc);
        free(t_alloc);
        return result;
    }
    else
    {
        for(; *s1 == *t1; s1++, t1++)
        {
            if(*s1 == '\0')
            {
                free(s_alloc);
                free(t_alloc);
                return 0;
            }
        }
        result = *s1 - *t1;
        free(s_alloc);
        free(t_alloc);
        return result;
    }
}

void str_trim(char *t, char *s)
{
    while(*s)
    {
        if(isalnum(*s) || *s == ' ')
        {
            *t++ = *s++;
        }
        else s++;
    }
    *t = *s;
}

void str_cpy(char *t, char *s)
{
    while((*t++ = *s++));
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

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