#include <stdio.h>

int rotate_r(int x);

/* Rotates the bits of an integer x to the right by one bit */
/* Didn't bother accounting for input error on this one */

int main(void)
{
    int x;

    printf("Integer: ");
    scanf("%d", &x);

    x = rotate_r(x);

    printf("Rotated integer: %d\n", x);

    return 0;
}

int rotate_r(int x)
{
    if(x%2 == 1) //If there's a one in the rightmost spot, move it to the leftmost
    {
        int p;
        float y = x;
        for(p=0; y>=2; y = y/2.0)
        {
            p++;
        }
        x = x >> 1;
        x = x | ((~(~0u << 1)) << p);
        /* This line generates a warning upon compilation, but 2-6 has seemingly the same code and doesn't.
        The problem is (~0 << 1) gets a warning because "shifting a negative signed value is undefined", but
        why is ~0 suddenly a negative signed value? Shouldn't it just be all ones? Perhaps having all ones
        creates a "TRUE" factor in the designated sign bit, but then why didn't 2-6 generate the same
        warning? */
        /* Update: fixed it by simply specifying 0 as unsigned (~0u << 1) */
        /* Should 1 be written as 01 instead? */
    }
    else //Otherwise simply shift right
    {
        x = x >> 1;
    }
    return x;
}