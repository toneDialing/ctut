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
struct key *binsearch(char *, struct key *, int);

/* Altered getword() to handle underscores, string constants, comments, and preprocessor control lines */

/* Count C keywords: pointer version */
int main(void)
{
    char word[MAXWORD];
    struct key *p;

    while(getword(word, MAXWORD) != EOF) /* Reads and counts keywords */
    {
        if(isalpha(word[0]))
        {
            if((p = binsearch(word, keytab, NKEYS)) != NULL)
            {
                p->count++;
            }
        }
    }
    for(p=keytab; p<(keytab+NKEYS); p++) /* Prints results */
    {
        if(p->count > 0)
        {
            printf("%4d %s\n", p->count, p->word);
        }
    }
    return 0;
}

/* binsearch: find word in tab[0], ..., tab[n-1]
    Returns position if found, -1 if not found */
struct key *binsearch(char *word, struct key *tab, int n)
{
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n]; //tab[n] is first element beyond end of array
                                //thus, dereferencing is illegal, but it's okay for pointer arithmetic
    struct key *mid;

    while(low<high)
    {
        mid = low + (high-low)/2;
        if((cond = strcmp(word, mid->word)) < 0)
        {
            high = mid;
        }
        else if(cond > 0)
        {
            low = mid+1;
        }
        else return mid;
    }
    return NULL;
}

int getch(void);
void ungetch(int);
void skip_irregular_text(int);
void skip_comment(void);
void skip_preprocessor(void);

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    /* ignore white space and other irregular text */
    while(isspace(c = getch()));
    if(c!=EOF)
    {
        *w++ = c;
    }
    if(!isalpha(c))
    {
        skip_irregular_text(c);
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

/* skip_irregular_text: causes getch() to skip over underscored words, string constants, comments and
    preprocessor control lines */
void skip_irregular_text(int c)
{
    switch(c) {
    case '_':
        while(isalnum(c=getch()));
        ungetch(c);
        break;
    case '"':
        while((c=getch())!='"');
        break;
    case '/':
        if((c=getch())=='*')
        {
            skip_comment();
        }
        else ungetch(c);
        break;
    case '#':
        skip_preprocessor();
        break;
    default:
        break;
    }
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