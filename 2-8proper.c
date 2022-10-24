#include <stdio.h>

int rotate_rn(int x, int n);

/* Rotates bits of an integer x rightward by a specified amount n */
/* Didn't bother accounting for invalid input */
/* It's likely more proper to use unsigned ints */

int main(void)
{
    int x, n;

    printf("Integer: ");
    scanf("%d", &x);
    printf("Number of bits to rotate: ");
    scanf("%d", &n);

    x = rotate_rn(x, n);
    printf("Rotated integer: %d\n", x);

    return 0;
}

int rotate_rn(int x, int n)
{
    int y = x & ~(~0 << n); //gets rightmost n bits of x and stores them in y

    int p;
    float f = x;
    for(p=0; f>=2; f = f/2.0) //finds length of x in bits and stores it in p (1st position is 0)
    {
        p++;
    }

    y = y << (p+1-n); //shifts y over to the leftmost position in x
    x = x >> n; //shifts leftmost part of x over to the right
    x = y | x; //combines x and y to complete rotation
    return x;
}