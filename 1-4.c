#include <stdio.h>

#define LOWER 0    /* lower limit of temperature table */
#define UPPER 300  /* upper limit of temperature table */
#define STEP  20    /* step size */

/* print Celsius-Fahrenheit table
    for celsius = 0, 20, ..., 300 */
// Floating point version!

int main(void)
{
    float fahr, celsius;

    celsius = LOWER; //note that lower is converted to float before operation is executed
    printf("Celsius\tFahrenheit\n");
    while(celsius <= UPPER)
    {
        fahr = (9.0/5.0)*celsius+32.0; //decimal point is needed to indicate that the constants are floats
        printf("%7.0f\t%10.1f\n", celsius, fahr);
        celsius = celsius + STEP;
    }
}