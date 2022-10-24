#include <stdio.h>

int setbits(int x, int p, int n, int y);

/* Inserts rightmost n bits of y into x at position p */
/* Didn't bother accounting for input error on this one */

int main(void)
{
    int x, p, n, y;

    printf("Integer 1: ");
    scanf("%d", &x);
    printf("Position: ");
    scanf("%d", &p);
    printf("Number of bits: ");
    scanf("%d", &n);
    printf("Integer 2: ");
    scanf("%d", &y);

    x = setbits(x, p, n, y);
    printf("New integer: %d\n", x);

    return 0;
}

int setbits(int x, int p, int n, int y) //assumes valid arguments
{
    y = y & ~(~0 << n); //gets rightmost n bits of y
    y = y << (p+1-n); //shifts y over to position p
    x = x & ((~0 << (p+1)) | ~(~0 << (p+1-n))); //converts n bits at position p to 0s, leaves rest of x unchanged
    x = x | y; // inserts new y into x at position p
    return x;
}