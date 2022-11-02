#include <stdio.h>
#include <stdlib.h> // for atof()
#include <ctype.h>
#include <math.h>

#define MAXOP 100 // max size of operand or operator
#define NUMBER '0' // signal that a number was found

/* My problem with this calculator is that I can't enter any input without triggering '\n'.
Perhaps there's a way to submit input without doing this, but I don't know what it is.
Because '\n' is triggered in the switch every time input is entered, it causes the calculator
to be a little buggy, but I'll ignore that feature for now because that's how K&R built it. */

/* Update: I've fixed this somewhat by adding a while loop to ignore subsequent input through '\n'
for certain commands, such as printing top of stack or assigning variables */

/* Aim to replace ungetch() with static internal variable in getop() */

int getop(char *s);
void push(double);
double pop(void);
void printstack(void);
void duplicate(void);
void swapstack(void);
void clearstack(void);

/* Reverse Polish calculator:
Input must be entered with spaces separating digits. Operator appears after necessary operands.
e.g. "4 5 +" equals 9 */
/* Add modulus operator */
/* Add negative numbers */
/* Add commands to print, duplicate, or swap top of stack */
/* Add access to functions sin, exp, and pow */
/* Add ability to assign values to variables x, y, and z */
/* Add ability to reference most recent answer in equations */
/* Add ability to quit without using EOF */
/* Largely assumes valid input */

int main(void)
{
    int type, intconvert, c;
    double op2, x, y, z, answer;
    char *s = malloc(MAXOP*sizeof(char));
    intconvert = 0; // Warns user of conversion to integer operands at any point in calculation

    printf("Welcome to the reverse Polish calculator!\n");
    printf("Begin entering operations or type 'g' for a guide\n");

    while((type = getop(s)) != EOF && type != 'q')
    {
        switch (type)
        {
            case 'g':
                printf("\tUse '+', '-', '*', and '/' for standard operations\n");
                printf("\tUse '%%' for mod (note all doubles will be truncated to integers)\n");
                printf("\tUse '~' for sin(x)\n");
                printf("\tUse 'e' for e^x\n");
                printf("\tUse '^' for x^y\n");
                printf("\tUse '=x' to assign a value to x (or likewise for y or z)\n");
                printf("\tUse 'a' to reference the most recent answer\n");
                printf("\tEnter 'p' to print top of stack\n");
                printf("\tEnter 'd' to duplicate top of stack\n");
                printf("\tEnter 's' to swap top two elements of stack\n");
                printf("\tEnter 'c' to clear the stack\n");
                printf("\tEnter 'q' to quit\n");
                while((c=getchar())!='\n')
                {
                    ;
                }
                break;
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
            case '~':
                push(sin(pop()));
                break;
            case 'e':
                push(exp(pop()));
                break;
            case '^':
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case '=':
                if((c=getchar())=='x') x = pop();
                else if(c=='y') y = pop();
                else if(c=='z') z = pop();
                else printf("error: undefined variable\n");
                while((c=getchar())!='\n')
                {
                    ;
                }
                break;
            case 'a':
                push(answer);
                break;
            case 'x':
                push(x);
                break;
            case 'y':
                push(y);
                break;
            case 'z':
                push(z);
                break;
            case 'p':
                printstack();
                while((c=getchar())!='\n')
                {
                    ;
                }
                break;
            case 'd':
                duplicate();
                while((c=getchar())!='\n')
                {
                    ;
                }
                break;
            case 's':
                swapstack();
                while((c=getchar())!='\n')
                {
                    ;
                }
                break;
            case 'c':
                clearstack();
                while((c=getchar())!='\n')
                {
                    ;
                }
                break;
            case '\n':
                answer = pop();
                printf("\t%.8g\n", answer);
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
double val[MAXVAL]; /* Note this array is initialized to all zeros ('\0') by default,
                    since it is a global variable */

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
    int i;
    for(i=0; val[i]!='\0' && i<MAXVAL; i++)
    {
        ;
    }

    if(i==0)
    {
        printf("error: stack empty\n");
    }
    else
    {
        printf("Top of stack: %g\n", val[--i]);
    }
}

/* Duplicate top element of stack */
void duplicate(void)
{
    int i;
    for(i=0; val[i]!='\0' && i<MAXVAL; i++)
    {
        ;
    }

    if(i==0)
    {
        printf("error: stack empty\n");
    }
    else if(i==MAXVAL)
    {
        printf("error: stack full\n");
    }
    else
    {
        int temp = i;
        val[temp] = val[--i];
    }
}

/* Swap top two elements of stack */
void swapstack(void)
{
    int i;
    for(i=0; val[i]!='\0' && i<MAXVAL; i++)
    {
        ;
    }

    if(i==0)
    {
        printf("error: stack empty\n");
    }
    else
    {
        int temp = i-2;
        double dtemp = val[--i];
        val[i] = val[temp];
        val[temp] = dtemp;
    }
}

/* Clears the stack */
void clearstack(void)
{
    for(int i=0; val[i]!='\0' && i<MAXVAL; i++)
    {
        val[i] = '\0';
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