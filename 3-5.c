#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAX 500

/* Converts an integer n to a specified base representation b and stores result in a string s */
/* Assumes valid input */
/* Unable to handle extreme integer values for reasons I don't yet understand.
Presumably there isn't enough storage to handle arithmetical calculations */

void inttobase(int n, char *s, int b);

int main(void)
{
    int n, b;
    char *s = malloc(MAX*sizeof(char));

    printf("Enter integer: ");
    scanf("%d", &n);
    printf("Enter base: ");
    scanf("%d", &b);

    inttobase(n, s, b);

    if(s[0]=='\0') printf("Error: Invalid base\n");
    else printf("Converted integer as string: %s\n", s);

    free(s);
    return 0;
}

void inttobase(int n, char *s, int b)
{
    int i, min;
    i = min = 0;

    if(n<0) //Stores a negative sign at front of string if necessary
    {
        if(n==INT_MIN)
        {
            n = INT_MAX;
            min = 1;
        }
        else n = -n; //This doesn't work for INT_MIN because its negative is one greater than INT_MAX
        s[i] = '-';
        i++;
    }

    if(n==0) //Handles the zero case
    {
        s[i++] = '0';
    }
    else if(b>=2 && b<=16) //Handles all non-zero cases from base 2 to 16 inclusive
    {
        int power = 0;
        int value = n;
        while(value>=b) //Find length of number in new base representation
        {
            value /= b;
            power++;
        }
        while(power>=0) //Convert number to new base and store in string s
        {
            int temp = pow(b, power);
            s[i] = '0';
            while(temp<=n)
            {
                if(s[i]=='9') s[i] = 'A';
                else s[i]++;
                temp += pow(b, power);
            }
            i++;
            n -= temp - pow(b, power);
            power -= 1;
        }
    }

    if(min) //If n==INT_MIN, add 1 to final result
    {
        if(s[i-1]=='9') s[i-1]='A';
        else s[i-1]++;
    }
    s[i] = '\0';
}