#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    printf("Data type sizes (in bytes):\n");
    printf("Char: %lu\n", sizeof(char));
    printf("Short int: %lu\n", sizeof(short int));
    printf("Int: %lu\n", sizeof(int));
    printf("Long int: %lu\n", sizeof(long int));
    printf("Float: %lu\n", sizeof(float));
    printf("Double: %lu\n", sizeof(double));
    printf("Long double: %lu\n\n", sizeof(long double));

    printf("Max and min sizes of data types:\n");
    printf("Char min: %d\n", CHAR_MIN);
    printf("Char max: %d\n", CHAR_MAX);
    printf("Unsigned char max: %u\n", UCHAR_MAX);
    printf("Short min: %d\n", SHRT_MIN);
    printf("Short max: %d\n", SHRT_MAX);
    printf("Unsigned short max: %u\n", USHRT_MAX);
    printf("Int min: %d\n", INT_MIN);
    printf("Int max: %d\n", INT_MAX);
    printf("Unsigned int max: %u\n", UINT_MAX);
    printf("Long min: %ld\n", LONG_MIN);
    printf("Long max: %ld\n", LONG_MAX);
    printf("Unsigned long max: %lu\n\n", ULONG_MAX);

    printf("----------Fun with floats!----------\n");
    printf("Radix of exponent's base: %d\n", FLT_RADIX);
    printf("Floating point rounding mode for addition: %d\n", FLT_ROUNDS);
    printf("Decimal digits of float precision: %d\n", FLT_DIG);
    printf("Smallest float recognized: %e\n", FLT_EPSILON);
    printf("Number of binary digits in mantissa: %d\n", FLT_MANT_DIG);
    printf("Maximum float: %e\n", FLT_MAX);
    printf("\tThis is (2^24 - 1)*(2^128/2^24)\n");
    printf("Maximum float exponent (given binary base): %d\n", FLT_MAX_EXP);
    printf("Minimum normalized float: %e\n", FLT_MIN);
    printf("\tThis is 2^(-126)\n");
    printf("Minimum float exponent (for normalization): %d\n\n", FLT_MIN_EXP);

    printf("Decimal digits of double precision: %d\n", DBL_DIG);
    printf("Smallest double recognized: %e\n", DBL_EPSILON);
    printf("Number of binary digits in mantissa: %d\n", DBL_MANT_DIG);
    printf("Maximum double: %e\n", DBL_MAX);
    printf("Maximum double exponent (given binary base): %d\n", DBL_MAX_EXP);
    printf("Minimum normalized double: %e\n", DBL_MIN);
    printf("Minimum double exponent (for normalization): %d\n\n", DBL_MIN_EXP);
}