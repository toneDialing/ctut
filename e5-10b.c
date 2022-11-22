#include <stdio.h>

/* echo command-line arguments; 2nd version */
int main(int argc, char *argv[])
{
    while(--argc>0)
    {
        printf((argc>1) ? "%s " : "%s", *++argv); /* note expressions can be placed
                                                    in the first argument of printf() */
    }
    printf("\n");
    return 0;
}