#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

/* Write a private version of scanf() analogous to minprintf() from the previous section */

/* minscanf() only handles conversion characters 'd', 'f', and 's', with no other
    format string specifications. Here, 'f' is assumed to be double instead of 'lf'. */
/* Assumes valid input */

int minscanf(char *, ...);

int main(void)
{
    int n;
    double d;
    char s[MAX_WORD_LENGTH];

    if(!minscanf("%d / %f / %s", &n, &d, s))
    {
        printf("Error: minscanf() failed to assign input items\n");
    }
    else
    {
        printf("%d %f %s\n", n, d, s);
    }

    return 0;
}

int minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int c, *ival;
    double *dval;
    int assigned_input_items = 0;

    va_start(ap, fmt);
    for(p = fmt; *p; p++)
    {
        if(*p==' ' || *p=='\t') /* skip blanks and tabs */
        {
            continue;
        }
        if(*p!='%') /* literal characters */
        {
            while(isspace(c=getchar()));
            if(c!=*p)
            {
                printf("Error: incorrect format for scanf()\n");
                return 0;
            }
        }
        else
        {
            switch(*++p){
            case 'd':
                ival = va_arg(ap, int *);
                scanf("%d", ival);
                assigned_input_items++;
                break;
            case 'f':
                dval = va_arg(ap, double *);
                scanf("%lf", dval);
                assigned_input_items++;
                break;
            case 's':
                sval = va_arg(ap, char *);
                scanf("%s", sval);
                assigned_input_items++;
                break;
            default:
                printf("Error: invalid conversion character\n");
                return 0;
            }
        }
    }
    va_end(ap);
    return assigned_input_items;
}