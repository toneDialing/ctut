#include <stdio.h>
#include <stdlib.h> // for atof()
#include <ctype.h>

#define MAXOP 100 // max size of operand or operator
#define NUMBER '0' // signal that a number was found

int getop(char *s);
void push(double);
double pop(void);

/* Reverse Polish calculator:
Input must be entered with spaces separating digits. Operator appears after necessary operands.
e.g. "4 5 +" equals 9 */

int main(void)
{
    int type;
    double op2;
    char *s = malloc(MAXOP*sizeof(char));

    while((type = getop(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2); /* Notice "pop() - pop()" wouldn't be consistently defined because
                                    the order in which each pop() is evaluated is not guaranteed by C */
                break;
            case '/':
                op2 = pop();
                if(op2!=0.0)
                {
                    push(pop() / op2);
                }
                else
                {
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    free(s);
    return 0;
}

#define MAXVAL 100 // Max depth of val stack

int sp = 0; // Next free stack position
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
    if(sp<MAXVAL)
    {
        val[sp++] = f;
    }
    else printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if(sp>0)
    {
        return val[--sp];
    }
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char *s)
{
    int i, c;

    while((s[0] = c = getch()) == ' ' || c == '\t')
    {
        ;
    }

    s[1] = '\0';
    if(!isdigit(c) && c!='.') // Not a number
    {
        return c;
    }
    i = 0;

    if(isdigit(c)) // Collect integer part
    {
        while(isdigit(s[++i] = c = getch()))
        {
            ;
        }
    }
    if(c=='.') // Collect fraction part
    {
        while(isdigit(s[++i] = c = getch()))
        {
            ;
        }
    }
    s[i] = '\0';

    if(c!=EOF)
    {
        ungetch(c);
    }
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; // Buffer for ungetch
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