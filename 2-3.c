#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 500 //Max input length

int hextoint(char *s, int len);
bool ishexdigit(int c);

/* Converts hex to decimal. 
Errors to be aware of:
Program doesn't protect against integer overflow
When reading user input, stops upon first encounter of non-hex input
If input is invalid, notifies user but doesn't return error or reprompt user */

int main(void)
{
    int c, n, len;
    char *s = malloc(MAX*sizeof(char));
    len = 0;

    printf("Howdy! Please enter a positive hexadecimal number: ");
    c = getchar();

    if(c=='0') //detects and skips over potential "0x" or "0X" prefixes
    {
        c = getchar();
        if(c=='x'||c=='X')
        {
            c = getchar();
        }
    }

    for(int i=0; ishexdigit(c); i++) //stores hex digits in array s, stopping upon non-hex input
    {
        s[i] = c;
        c = getchar();
        len++;
    }
    s[len]='\0';

    n = hextoint(s, len);
    if(n==0) //if input is invalid, notify user but don't return error
    {
        printf("Error: Invalid input\n");
    }
    else
    {
        printf("Your number is: %d\n", n);
    }

    free(s);
    return 0;
}

int hextoint(char *s, int len) //converts hex to decimal, assuming valid input
{
    int n = 0;

    for(int i = 0; i<len; i++)
    {
        if(s[i]>='0' && s[i]<='9')
        {
            n = 16*n + (s[i]-'0');
        }
        else if(s[i]>='a' && s[i]<='f')
        {
            n = 16*n + (s[i]-'a') + 10;
        }
        else
        {
            n = 16*n + (s[i]-'A') + 10;
        }
    }
    return n;
}

bool ishexdigit(int c)
{
    if((c>='0' && c<= '9') || (c>='a' && c<='f') || (c>='A' && c<='F'))
    {
        return 1;
    }
    else return 0;
}