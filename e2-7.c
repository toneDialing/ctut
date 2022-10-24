#include <stdio.h>
#include <stdlib.h>

#define MAX 500

int chartoint(char *s); //Converts s to an int
/* Note that this code has no error protection against integer overflow */

int main(void)
{
    int n, c;
    char *s = malloc(MAX*sizeof(char));

    printf("Wassup! Please enter some numbers without spaces: ");
    for(int i=0; (c=getchar())!='\n' && i<MAX; i++)
    {
        if(c==EOF)
        {
            return 1;
        }
        s[i] = c;
    }

    n = chartoint(s);
    printf("Presto! Now it's a number: %d\n", n);
    
    free(s);
    return 0;
}

int chartoint(char *s)
{
    int i, n;

    n = 0;
    for(i=0; s[i] >= '0' && s[i] <= '9'; i++) //this can be replaced by isdigit()
    {
        n = 10*n + (s[i] - '0');
    }
    return n;
}