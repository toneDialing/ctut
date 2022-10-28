#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 500

/* Converts a string to a float, accounting for sign, decimal point, and exponent */
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
    double val, power, exp;
    int i, sign, exp_sign;

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

    if(s[i]=='e' || s[i]=='E')
    {
        i++;
    }
    exp_sign = (s[i]=='-') ? -1 : 1; // !! fix if no E/e
    if(s[i]=='+' || s[i]=='-')
    {
        i++;
    }

    for(exp=0.0; isdigit(s[i]); i++)
    {
        exp = 10.0*exp + (s[i]-'0');
    }

    return sign*(val/power) * pow(10.0, exp_sign*exp);
}