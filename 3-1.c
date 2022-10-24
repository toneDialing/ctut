#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500

/* Finds integer x in sorted integer array v[] */
/* Didn't account for input error */

int binsearch(int x, int *v, int n);

int main(void)
{
    int x, pos;
    int n = 100; //Artificially chose an array of size 100 for simplicity
    int *v = malloc(MAX*sizeof(int));

    for(int i=0; i<n; i++)
    {
        v[i] = i;
    }

    printf("Integer: ");
    scanf("%d", &x);

    clock_t begin = clock(); //This doesn't seem to be a reliable way to measure run-time
    pos = binsearch(x, v, n);
    clock_t end = clock();
    double time_spent = (double)(end - begin)/CLOCKS_PER_SEC;

    if(pos!=(-1)) printf("Integer found at position %d\n", pos);
    else printf("Integer not found\n");

    printf("Run time: %f\n", time_spent);

    free(v);
    return 0;
}

/* Rewritten from e3-3 so that now only one test is made *inside* the while loop.
I was unable to reliably measure the difference in run-time between the two approaches,
as using clock() seems to be the wrong approach. Will try to measure run-time again
later once I learn the right approach. */
int binsearch(int x, int *v, int n)
{
    int low, high, mid;

    low = 0;
    high = n-1;
    while(low<high)
    {
        mid = (low+high)/2;
        if(x<=v[mid])
        {
            high = mid;
        }
        else low = mid+1;
    }
    if(x==v[low]) return low;
    else return -1;
}