#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

/* allow for trailing spaces/tabs after declaration */
/* if there's an error, be able to reset (while != '\n') *
* Fixed within main() so far, check rest of code for error prints */
/* if no data type, assume int */
/* ^^ actually this encourages bad practice and may no longer be true with updated C anyway,
    so don't support this option */

enum {NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int getch(void);
void ungetch(int);
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */

/* Convert declaration syntax into plain words */
int main(void)
{
    while(gettoken() != EOF)
    {
        strcpy(datatype, token);    /* 1st token on line is the data type */
        out[0] = '\0';
        dcl();                      /* parse rest of line */
        while(tokentype == ' ' || tokentype == '\t')
        {
            tokentype = getch();
        }
        if(tokentype != '\n')
        {
            while((tokentype = getch())!='\n');
            printf("syntax error\n");
        }
        else
        {
            printf("%s: %s %s\n", name, out, datatype);
        }
    }
    return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;

    for(ns=0; gettoken()=='*'; ) /* count # of *'s */
    {
        ns++;
    }
    dirdcl();
    while(ns-- > 0)
    {
        strcat(out, " pointer to");
    }
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;

    if(tokentype == '(') /* (dcl) */
    {
        dcl();
        if(tokentype != ')')
        {
            printf("error: missing )\n");
        }
    }
    else if(tokentype == NAME) /* variable name */
    {
        strcpy(name, token);
    }
    else
    {
        printf("error: expected name or (dcl)\n");
    }

    while((type = gettoken()) == PARENS || type == BRACKETS)
    {
        if(type == PARENS)
        {
            strcat(out, " function returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

/* gettoken: return next token */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while((c=getch()) == ' ' || c == '\t')
    {
        ;
    }
    if(c=='(')
    {
        if((c=getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if(c == '[')
    {
        for(*p++ = c; (*p++ = getch()) != ']'; )
        {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if(isalpha(c))
    {
        for(*p++ = c; isalnum(c=getch()); )
        {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else return tokentype = c;
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