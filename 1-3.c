#include <stdio.h>

/* print Fahrenheit-Celsius table
    for fahr = 0, 20, ..., 300 */
// Floating point version!

int main(void)
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit of temperature table */
    step = 20;      /* step size */

    fahr = lower; //note that lower is converted to float before operation is executed
    printf("Fahrenheit\tCelsius\n");
    while(fahr <= upper)
    {
        celsius = (5.0/9.0)*(fahr-32.0); //decimal point is needed to indicate that the constants are floats
        printf("%10.0f\t%7.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}