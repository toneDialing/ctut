#include <stdio.h>
#include <stdarg.h>

/* Write a private version of scanf() analogous to minprintf() from the previous section */

int minscanf(char *, ...);

int main(void)
{
    int n;

    minscanf("%d", &n);
    printf("%d\n", n);

    return 0;
}

int minscanf(char *fmt, ...)
{
    va_list ap;
    char *p;
    int c;

    va_start(ap, fmt);
    for(p = fmt; *p; p++)
    {
        if(*p==' ' || *p=='\t') /* skip blanks and tabs */
        {
            continue;
        }
        if(*p!='%') /* literal characters */
        {
            if((c = getchar())!=*p)
            {
                printf("Error: incorrect format for scanf()\n");
                return 0;
            }
        }
    }
    va_end(ap);
    /* add return value */
}