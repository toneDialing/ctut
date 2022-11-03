#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Converts an int to a string using recursion.
Doesn't work if n is largest negative integer, as its positive equivalent is too large to store */

void inttostring(int n, char *s);

int main(void)
{
    int n;
    char *s = malloc(MAX*sizeof(char));

    printf("Integer: ");
    scanf("%d", &n);

    inttostring(n, s);
    printf("Integer as string: %s\n", s);

    free(s);
    return 0;
}

void inttostring(int n, char *s)
{
    static int i = 0;

    if(n<0)
    {
        s[i++] = '-';
        n = -n; //note this is impossible if n is largest negative integer
    }

    if(n/10)
    {
        inttostring(n/10, s);
    }
    s[i++] = n % 10 + '0';
    s[i] = '\0';
}