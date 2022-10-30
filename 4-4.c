#include <stdio.h>
#include <stdlib.h> // for atof()
#include <ctype.h>

#define MAXOP 100 // max size of operand or operator
#define NUMBER '0' // signal that a number was found

int getop(char *s);
void push(double);
double pop(void);
void printstack(void);
void duplicate(void);
void swapstack(void);

/* Reverse Polish calculator:
Input must be entered with spaces separating digits. Operator appears after necessary operands.
e.g. "4 5 +" equals 9 */
/* Add modulus operator */
/* Add negative numbers */
/* Add commands to print, duplicate, or swap top of stack */
/* Largely assumes valid input */

int main(void)
{
    int type, intconvert;
    double op2;
    char *s = malloc(MAXOP*sizeof(char));
    intconvert = 0; // Warns user of conversion to integer operands at any point in calculation

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
            case '%':
                op2 = pop();
                if(op2!=0.0)
                {
                    push(((int) pop()) % ((int) op2));
                    intconvert = 1;
                }
                else
                {
                    printf("error: zero divisor\n");
                    /* Perhaps not actually an error, depending on how
                    mod is defined */
                }
                break;
            case 'p':
                printstack();
                break;
            case 'd':
                duplicate();
                break;
            case 's':
                swapstack();
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                if(intconvert)
                {
                    printf("\tWarning: decimal truncation may have occurred\n");
                    intconvert = 0;
                }
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

/* Print top element of stack */
void printstack(void)
{
    if(sp>0)
    {
        printf("%g\n", val[sp-1]);
    }
    else
    {
        printf("error: stack empty\n");
    }
}

/* Duplicate top element of stack */
void duplicate(void)
{
    if(sp>0 && sp<MAXVAL)
    {
        val[sp] = val[sp - 1];
        sp++;
    }
    else if(sp<=0)
    {
        printf("error: stack empty\n");
    }
    else
    {
        printf("error: stack full\n");
    }
}

/* Swap top two elements of stack */
void swapstack(void)
{
    if(sp>1)
    {
        double temp = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = val[sp-1];
    }
    else
    {
        printf("error: stack has 1 or fewer elements\n");
    }
}

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char *s)
{
    int i, c, c_spare;

    while((s[0] = c = getch()) == ' ' || c == '\t')
    {
        ;
    }
    s[1] = '\0';

    if(!isdigit(c) && c!='.' && c!='-') // Not a number
    {
        return c;
    }
    i = 0;

    if(c=='-') // Check to see if '-' denotes a negative number or a minus sign
    {
        s[1] = c_spare = getch();
        ungetch(c_spare);
        if(!isdigit(c_spare))
        {
            return c;
        }
        c = c_spare;
    }

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