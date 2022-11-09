#include <stdio.h>

// Defines a macro swap(t, x, y) that interchanges two arguments of type t

#define swap(t, x, y)   t temp = x; \
                        x = y; \
                        y = temp
// Note absence of terminating semicolon in #define to allow for presence of semicolon in code
/* Techinically this isn't necessary as a duplicated ; simply creates an empty statement,
    but it's slightly cleaner */

/* Hard-coded for simplicity */
int main(void)
{
    int x = 5;
    int y = 6;

    swap(int, x, y);

    printf("x: %d\ny: %d\n", x, y);

    return 0;
}