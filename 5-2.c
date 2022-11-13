#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/* Modified getint() to perform ungetch() if it encounters an isolated '+' or '-' */

/* Create getfloat() */

int getfloat(double *pn);

int main(void)
{
    double *pn = malloc(sizeof(double));

    printf("Hello! Please enter number: ");
    if(getfloat(pn)>0)
    {
        printf("Your number: %g\n", *pn);
    }
    else printf("Invalid input\n");

    free(pn);
    return 0;
}

int getch(void);
void ungetch(int);

/* getfloat: get next digit from input into *pn, allowing for sign and decimal point */
int getfloat(double *pn)
{
    int c, i, sign;

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
    if(c=='.')
    {
        c = getch();
    }
    for(i=1; isdigit(c); c = getch(), i++)
    {
        *pn = *pn + (c-'0')/(pow(10, i));
        /* IMPORTANT NOTE: The division operation must contain at least one double to avoid
        integer evaluation, which would be 0. However, pow() automatically converts i and 10
        to doubles so it isn't necessary to write 10.0 here. */
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