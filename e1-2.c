#include <stdio.h>

/* print Fahrenheit-Celsius table
    for fahr = 0, 20, ..., 300 */

int main(void)
{
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit of temperature table */
    step = 20;      /* step size */

    fahr = lower;
    while(fahr <= upper)
    {
        celsius = 5*(fahr-32)/9; // divide by 9 last to minimize issues of integer truncation!
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }
}