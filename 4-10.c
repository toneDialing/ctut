#include <stdio.h>
#include <stdlib.h> // for atof()
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100 // max size of operand or operator
#define NUMBER '0' // signal that a number was found

/* My problem with this calculator is that I can't enter any input without triggering '\n'.
Perhaps there's a way to submit input without doing this, but I don't know what it is.
Because '\n' is triggered in the switch every time input is entered, it causes the calculator
to be a little buggy, but I'll ignore that feature for now because that's how K&R built it. */

/* Update: I've fixed this somewhat by adding a while loop to ignore subsequent input through '\n'
for certain commands, such as printing top of stack or assigning variables */

/* Replaces getch() and ungetch() with readline() */

void push(double);
double pop(void);
void printstack(void);
void duplicate(void);
void swapstack(void);
void clearstack(void);
int readline(char *s, int lim);

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
    int type, intconvert, minus, c, i, j;
    double op2, x, y, z, answer;
    char *s = malloc(MAXOP*sizeof(char));
    char *num = malloc(MAXOP*sizeof(char));
    intconvert = 0; // Warns user of conversion to integer operands at any point in calculation

    printf("Welcome to the reverse Polish calculator!\n");
    printf("Begin entering operations or type 'g' for a guide\n");

    while((readline(s, MAXOP)) > 0)
    {
        for(i=0; i<strlen(s); i++)
        {
        j = minus = 0;

        if(!isdigit(s[i]) && s[i]!='.' && s[i]!='-') //delete - case
        {
        switch (s[i])
        {
            case ' ':
                break;
            case '\t':
                break;
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
                while(s[++i]!='\n')
                {
                    ;
                }
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
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
                if(s[++i]=='x') x = pop();
                else if(s[i]=='y') y = pop();
                else if(s[i]=='z') z = pop();
                else printf("error: undefined variable\n");
                while(s[++i]!='\n')
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
                while(s[++i]!='\n')
                {
                    ;
                }
                break;
            case 'd':
                duplicate();
                while(s[++i]!='\n')
                {
                    ;
                }
                break;
            case 's':
                swapstack();
                while(s[++i]!='\n')
                {
                    ;
                }
                break;
            case 'c':
                clearstack();
                while(s[++i]!='\n')
                {
                    ;
                }
                break;
            case 'q':
                return 0;
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
                printf("error: unknown command %c\n", s[i]);
                break;
        }
        }
        else
        {
            if(s[i]=='-')
            {
                if(!isdigit(s[i+1]))
                {
                    op2 = pop();
                    push(pop() - op2); //Need to break out of big else here to avoid push below
                    minus = 1;
                }
                else
                {
                    num[j++] = s[i++];
                }
            }

            while(isdigit(s[i]))
            {
                num[j++] = s[i++];
            }

            if(s[i]=='.')
            {
                if(!isdigit(s[i+1]))
                {
                    printf("error: unknown command%c\n", s[i]);
                }
                else
                {
                    num[j++] = s[i++];
                }
            }

            while(isdigit(s[i]))
            {
                num[j++] = s[i++];
            }

            if(minus==0)
            {
                num[j] = '\0';
                push(atof(num));
                while(j>0)
                {
                    num[--j] = '\0';
                }
            }
        }
        }
    }

    free(s);
    free(num);
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

int readline(char *s, int lim)
{
    int c, i;

    i = 0;
    while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }
    if(c=='\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';

    return i;
}