#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARG_SIZE 10

/* Revise minprintf() to handle more of the other facilities of printf() */

/* I added capabilities for width specification and left alignment */
/* Assumes valid input */

void minprintf(char *, ...);

int main(void)
{
    int n = 3;

    minprintf("hello, world %-5d.\n", n);

    return 0;
}

/* minprintf(): minimal printf() with variable-length argument list */
void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed argument in turn */
    char *p, *sval, field_width_string[MAX_ARG_SIZE];
    int ival, field_width, width_specified, left_align;
    double dval;
    left_align = width_specified = 0;

    va_start(ap, fmt); /* make ap point to 1st unnamed argument */
    for(p = fmt; *p; p++)
    {
        field_width = 0;
        if(*p!='%')
        {
            putchar(*p);
            continue;
        }
        if(*++p=='-') /* Check for left alignment */
        {
            left_align = 1;
        }
        else p--;
        if(isdigit(*++p)) /* Check for width specification */
        {
            width_specified = 1;
            int i;
            for(i=0; isdigit(*p); i++, p++)
            {
                field_width_string[i] = *p;
            }
            field_width_string[i] = '\0';
            field_width = atoi(field_width_string);
            p--;
        }
        else p--;
        switch(*++p) { /* Parse conversion character */
        case 'd':
            ival = va_arg(ap, int);
            if(width_specified)
            {
                printf((left_align ? "%-*d" : "%*d"), field_width, ival);
            }
            else printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            if(width_specified)
            {
                printf((left_align ? "%-*f" : "%*f"), field_width, dval);
            }
            else printf("%f", dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            if(width_specified)
            {
                printf((left_align ? "%-*s" : "%*s"), field_width, sval);
            }
            else printf("%s", sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap); /* clean up when done */
}