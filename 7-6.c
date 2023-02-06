#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

/* Write a program to compare two files, printing the first line where they differ */

/* As written, file names must be entered as command line arguments */
/* This code is very simple but as yet doesn't handle errors */

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");

    while(!strcmp(fgets(line1, MAX_LINE_LENGTH, fp1), fgets(line2, MAX_LINE_LENGTH, fp2)))
    {
        ;
    }
    printf("File %s:\n%s\nFile %s:\n%s\n", argv[1], line1, argv[2], line2);
        /* Extra newline characters are almost certainly redundant, but it doesn't hurt
            to have them just in case */
    
    fclose(fp1);
    fclose(fp2);
    return 0;
}