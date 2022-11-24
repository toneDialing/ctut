#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Create a reverse Polish calculator that functions entirely within the command line */
/* Don't need to store variables or do advanced operations */

/* Pull code from previous Polish calculator */
/* Need push() and pop() from 4-10.c, don't need readline(), need atof() and much of 4-10's main() */

void push(double);
double pop(void);

int main(int argc, char *argv[])
{
    int c;
    double op2, answer;

    for(int i = 1; i<argc; i++)
    {
        c=*argv[i];
        if(!isdigit(c) && c != '.' && c != '-')
        {
            switch(c)
            {
                case ' ':
                    break;
                case '\t':
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
                default:
                    printf("error: unknown command %c\n", s[i]);
                    break;
            }
        }
        else
        {
            if(c=='-')
            {
                if(!*++argv[i])
                {
                    op2 = pop();
                    push(pop() - op2);
                }
                else
                {
                    push(atof(*argv[i]));
                }
            }
            else
            {
                push(atof(*argv[i]));
            }
        }
    }

    answer = pop();
    printf("\t%.8g\n", answer);

    return 0;
}

#define MAXVAL 100

int stack_position = 0;
double stack[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
    if(stack_position<MAXVAL)
    {
        stack[stack_position++] = f;
    }
    else printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if(stack_position>0)
    {
        return stack[--stack_position];
    }
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}