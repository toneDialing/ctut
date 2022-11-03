#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

/* Reverses a string using recursion */

void reverse(char *s);

int main(void)
{
    int i, c;
    char *s = malloc(MAX*sizeof(char));
    i = 0;

    printf("Enter string: ");
    while((c=getchar()) != '\n' && c!=EOF && i<(MAX-1))
    {
        s[i++] = c;
    }
    s[i] = '\0';

    reverse(s);
    printf("Reversed string: %s\n", s);

    free(s);
    return 0;
}

void reverse(char *s)
{
    static int first;
    if(first>=(strlen(s) - 1))
        return; //remember braces would be needed for multiple statements; absence here is aesthetic
    
    int n = strlen(s) - 1;

    while(n>first)
    {
        char temp = s[n-1];
        s[n-1] = s[n];
        s[n--] = temp;
    }
    first++;
    reverse(s);
}
