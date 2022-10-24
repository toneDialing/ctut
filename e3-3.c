#include <stdio.h>

#define MAX 100

int binsearch(int x, int *v, int n);

int main(void)
{
    int x, n;
    int *v;

    for(int i=0; i<MAX; i++)
    {
        
    }
}

int binsearch(int x, int *v, int n)
{
    int low, high, mid;

    low = 0;
    high = n-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(x<v[mid]);
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