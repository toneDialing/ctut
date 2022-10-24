#include <stdio.h>

int bitcount(int x);

/* Counts the number of 1 bits in an integer x, assuming a two's complement number system */
/* Assumes valid input */

int main(void)
{
    int x, b;

    printf("Integer: ");
    scanf("%d", &x);

    b = bitcount(x);

    printf("Number of 1 bits: %d\n", b);

    return 0;
}

int bitcount(int x)
{
    int b;
    while(x!=0)
    {
        x &= (x-1);
        b++;
    }
    return b;
}