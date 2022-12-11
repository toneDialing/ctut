#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS ((sizeof keytab) / (sizeof keytab[0])) //number of elements in keytab[]

struct key
{
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* Altered getword() to handle underscores, string constants, comments, and preprocessor control lines */

/* Count C keywords */
int main(void)
{
    int n;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF) /* Reads and counts keywords */
    {
        if(isalpha(word[0]))
        {
            if((n = binsearch(word, keytab, NKEYS)) >= 0)
            {
                keytab[n].count++;
            }
        }
    }
    for(n=0; n<NKEYS; n++) /* Prints results */
    {
        if(keytab[n].count > 0)
        {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    return 0;
}

/* binsearch: find word in tab[0], ..., tab[n-1]
    Returns position if found, -1 if not found */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if((cond = strcmp(word, tab[mid].word)) < 0)
        {
            high = mid-1;
        }
        else if(cond > 0)
        {
            low = mid+1;
        }
        else return mid;
    }
    return -1;
}

int getch(void);
void ungetch(int);
void skip_comment(void);
void skip_preprocessor(void);

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while(isspace(c = getch()));

    if(c!=EOF)
    {
        *w++ = c;
    }
    if(!isalpha(c))
    {
        int temp;
        if(c=='_')
        {
            while(isalnum(temp = getch()));
            ungetch(temp);
        }
        else if(c=='"')
        {
            while((temp=getch())!='"');
        }
        else if(c=='/')
        {
            if((temp = getch())=='*')
            {
                skip_comment();
            }
            else ungetch(temp);
        }
        else if(c=='#')
        {
            skip_preprocessor();
        }
        *w = '\0';
        return c;
    }
    for(; --lim>0; w++)
    {
        if(!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

/* skip_comment: causes getch() to skip over all text through end of comment */
void skip_comment(void)
{
    int c;

    while((c=getch())!=EOF)
    {
        if(c=='*')
        {
            if((c=getch())=='/') return;
            ungetch(c);
        }
    }
    ungetch(c);
}

/* skip_preprocessor: causes getch() to skip over all text through end of preprocessor control line(s) */
void skip_preprocessor(void)
{
    int c, temp;

    while((c=getch())!=EOF)
    {
        temp = c;
        if((c=getch())=='\n')
        {
            if(temp!='\\') return;
        }
        ungetch(c);
    }
    ungetch(c);
}

#define BUFSIZE 100

int buf[BUFSIZE]; // Buffer for ungetch, changed to type int to handle EOF
int bufp = 0; // Next free position in buf

/* Get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Push character back on input */
void ungetch(int c)
{
    if(bufp>=BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else buf[bufp++] = c;
}