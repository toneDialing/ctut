#include <stdio.h>
#include <stdlib.h>

#define MAX 500

/* Finds integer x in sorted integer array v[] */
/* Didn't account for input error */

int binsearch(int x, int *v, int n);

int main(void)
{
    int x, pos;
    int n = 100;
    int *v = malloc(MAX*sizeof(int));

    for(int i=0; i<n; i++)
    {
        v[i] = i;
    }

    printf("Integer: ");
    scanf("%d", &x);

    pos = binsearch(x, v, n);

    if(pos!=(-1)) printf("Integer found at position %d\n", pos);
    else printf("Integer not found\n");

    free(v);
    return 0;
}

int binsearch(int x, int *v, int n)
{
    int low, high, mid;

    low = 0;
    high = n-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(x<v[mid])
        {
            high = mid - 1;
        }
        else if(x>v[mid])
        {
            low = mid +1;
        }
        else return mid;
    }
    return -1;
}