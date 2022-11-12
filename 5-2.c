#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Modified getint() to perform ungetch() if it encounters an isolated '+' or '-' */

/* Create getfloat() */

int getint(int *pn);

int main(void)
{
    int *pn = malloc(sizeof(int));

    printf("Hello! Please enter integer: ");
    if(getint(pn)>0)
    {
        printf("Your integer: %d\n", *pn);
    }
    else printf("Invalid input\n");

    free(pn);
    return 0;
}

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while(isspace(c = getch())) //skip white space
        ;

    if(!isdigit(c) && c!=EOF && c!='+' && c!='-')
    {
        ungetch(c); //it's not a number
        return 0;
    }

    sign = (c=='-') ? -1 : 1;
    if(c=='+'||c=='-')
    {
        c = getch();
        if(!isdigit(c)) return 0;
    }

    for(*pn=0; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c-'0');
    }
    *pn *= sign;

    if(c!=EOF)
    {
        ungetch(c);
    }
    return c;
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