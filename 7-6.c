#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

/* Write a program to compare two files, printing the first line where they differ */

/* As written, file names must be entered as command line arguments */
/* If files match exactly, then the last line for each file is printed as "EOF". This is
    technically a bit sloppy because the line "EOF" could actually appear in a file, but
    it's perfectly sufficient for this small exercise. Easy fix is to print something else
    entirely upon reaching EOF by preceding the final printf() with an if statement. */

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];
    char *file1_status, *file2_status;

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");

    while((file1_status = fgets(line1, MAX_LINE_LENGTH, fp1))!=NULL)
    {
        if((file2_status = fgets(line2, MAX_LINE_LENGTH, fp2))==NULL)
        {
            strcpy(line2, "EOF");
            break;
        }
        else
        {
            if(strcmp(line1, line2)) break;
        }
    }
    if(file1_status==NULL)
    {
        strcpy(line1, "EOF");
        if((file2_status = fgets(line2, MAX_LINE_LENGTH, fp2))==NULL)
        {
            strcpy(line2, "EOF");
        }
    }

    printf("File %s:\n%s\nFile %s:\n%s\n", argv[1], line1, argv[2], line2);
        /* Extra newline characters are almost certainly redundant, but it doesn't hurt
            to have them just in case */
    
    fclose(fp1);
    fclose(fp2);
    return 0;
}