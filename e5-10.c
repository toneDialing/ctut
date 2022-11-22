#include <stdio.h>

/* echo command-line arguments: 1st version */
/* Apostrophes seem to mess up the reading of command-line arguments */
int main(int argc, char *argv[])
{
    int i;

    for(i=1; i<argc; i++)
    {
        printf("%s%s", argv[i], (i<argc) ? " " : "");
    }
    printf("\n");
    return 0;
}