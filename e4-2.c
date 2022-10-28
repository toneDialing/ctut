#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 500

/* Converts a string to a float, accounting for sign and decimal point */
/* Assumes valid input */

double stringtofloat(char *s);

int main(void)
{
    int c, i;
    char *s = malloc(MAX*sizeof(char));
    i = 0;

    while((c=getchar())!='\n' && c!=EOF)
    {
        s[i++] = c;
    }
    s[i] = '\0';

    double f = stringtofloat(s);

    printf("%f\n", f);

    free(s);
    return 0;
}

double stringtofloat(char *s)
{
    double val, power;
    int i, sign;

    for(i=0; isspace(s[i]); i++) //Skips white space
    {
        ;
    }
    sign = (s[i]=='-') ? -1 : 1;
    if(s[i]=='+' || s[i]=='-')
    {
        i++;
    }

    for(val=0.0; isdigit(s[i]); i++)
    {
        val = 10.0*val + (s[i] - '0');
    }
    if(s[i]=='.')
    {
        i++;
    }
    for(power=1.0; isdigit(s[i]); i++)
    {
        val = 10.0*val + (s[i]-'0');
        power *= 10.0;
    }

    return sign*(val/power);
}