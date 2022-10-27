#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 500

void expand(char *s, char *t);

/* Converts abbreviated notation into expanded notation. For example, c-g becomes cdefg, and 3-7
becomes 34567. Only expands notation that is moving "forward", i.e. 7-5 or z-a won't be expanded.
If letters are of different cases, expand according to the case of the first letter, so B-e becomes
BCDE. In the rare case of something like a-D-g, string would become abcdEFG. I feel this case is too
random to bother accounting for more properly, and a user should quickly learn not to input this way.
*/

int main(void)
{
    int c, i;
    char *s = malloc(MAX*sizeof(char));
    char *t = malloc(MAX*sizeof(char));
    i = 0;

    printf("Enter string: ");
    while((c=getchar())!='\n' && c!=EOF)
    {
        s[i++] = c;
    }
    s[i] = '\0';

    expand(s, t);

    printf("New string: %s\n", t);

    free(s);
    free(t);
    return 0;
}

void expand(char *s, char *t)
{
    int j = 0;
    for(int i=0; s[i]!='\0' && j<(MAX-1); i++)
    {
        if(s[i] == '-')
        {
            if(isalpha(s[i-1]) && isalpha(s[i+1]))
            {
                if(toupper(s[i+1]) - toupper(s[i-1]) <= 0) //values must be same case before comparing
                {
                    t[j++] = s[i];
                }
                else if(isupper(s[i-1]))
                {
                    int uppertemp = toupper(s[i+1]);
                    /* If first letter is uppercase, treat all letters as uppercase */
                    for(int k = 0; k < (uppertemp - s[i-1]); k++)
                    {
                        t[j++] = (char) s[i-1] + k + 1;
                    }
                    i++; //avoids doubling final char of abbreviated notation
                }
                else
                {
                    int lowertemp = tolower(s[i+1]);
                    /* If first letter is lowercase, treat all letters as lowercase */
                    for(int k = 0; k < (lowertemp - s[i-1]); k++)
                    {
                        t[j++] = (char) s[i-1] + k + 1;
                    }
                    i++; //avoids doubling final char of abbreviated notation
                }
            }
            else if(isnumber(s[i-1]) && isnumber(s[i+1]))
            {
                if(s[i+1] - s[i-1] <= 0)
                {
                    t[j++] = s[i];
                }
                else
                {
                    for(int k = 0; k < (s[i+1] - s[i-1]); k++)
                    {
                        t[j++] = (char) s[i-1] + k + 1;
                    }
                    i++; //avoid doubling final char of abbreviated notation
                }
            }
            else
            {
                t[j++] = s[i];
            }
        }
        else
        {
            t[j++] = s[i];
        }
    }
    t[j] = '\0';
}
