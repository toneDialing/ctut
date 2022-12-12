#include <stdio.h>

/* Write a program that reads a C program and prints in alphabetical order each group of variable names
    that are identical in the first 6 characters, but different somewhere thereafter. Don't count words
    within strings and comments. Make 6 a parameter that can be set from the command line. */

/* How to find variable names:
    Look for data type, and valid word that follows is a variable unless it is immediately followed by '('
    Data types:
        char
        int
        float
        double
        short   (if encountered, check if next word is also data type)
        long    (if encountered, check if next word is also data type)
        void *
            In all cases, check for subsequent *'s (potentially multiple)
        
        struct is a little more complicated. It could be:
            struct tag x
            struct tag {...} x
            struct {...} x
        All with potential subsequent *'s
*/

int main(void)
{

}