#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX 500

/* Converts int to string (of a minimum width) */
/* Assumes valid input in range between INT_MIN and INT_MAX */

void inttochar(int n, char *s, int minwidth);
void reverse(char *s);

int main(void)
{
    int n, minwidth;
    char *s = malloc(MAX*sizeof(char));

    printf("Enter integer: ");
    scanf("%d", &n);
    printf("Enter minimum width: ");
    scanf("%d", &minwidth);

    inttochar(n, s, minwidth);

    printf("Integer as string: %s\n", s);

    free(s);
    return 0;
}

void inttochar(int n, char *s, int minwidth)
{
    int i, sign;
    int min = 0; //Bool var meant to flag presence of INT_MIN

    if(n==INT_MIN)
    /*There's probably a better way to handle INT_MIN, but trying to cast n to an unsigned int wasn't
    working as expected */
    {
        n = INT_MAX;
        sign = -1;
        min = 1;
    }
    else if((sign=n)<0)
    {
        n = -n; //This doesn't work for INT_MIN because its negative is one greater than INT_MAX
    }
    i = 0;

    do
    {
        s[i++] = n%10 + '0';
    }
    while((n/=10) > 0);

    if(sign<0)
    {
        s[i++] = '-';
    }

    if(min)
    {
        if(s[0]=='9') s[0] = '0';
        else s[0]++;
    }

    while(i<minwidth)
    {
        s[i++] = ' ';
    }
    s[i] = '\0';

    reverse(s);
}

void reverse(char *s)
{
    int c, i, j;

    for(i=0, j=strlen(s)-1; i<j; i++, j--)
    {
        c=s[i], s[i]=s[j], s[j]=c;
    }
}