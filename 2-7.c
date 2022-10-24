#include <stdio.h>

int invertbits(int x, int p, int n);

/* Inverts n bits of x at position p */
/* Didn't bother accounting for input error on this one */

int main(void)
{
    int x, p, n, y;

    printf("Integer: ");
    scanf("%d", &x);
    printf("Position: ");
    scanf("%d", &p);
    printf("Number of bits: ");
    scanf("%d", &n);

    x = invertbits(x, p, n);
    printf("New integer: %d\n", x);

    return 0;
}

int invertbits(int x, int p, int n) //assumes valid arguments
{
    x = x ^ ((~(~0 << (n))) << (p+1-n));
    return x;
}