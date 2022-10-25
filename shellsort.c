#include <stdio.h>
#include <stdlib.h>

#define MAX 10

/* Sorts an array of integers using Shell sort, assuming valid input */

void shellsort(int *v, int n);

int main(void)
{
    int *v = malloc(MAX*sizeof(int));

    for(int i=0; i<MAX; i++)
    {
        printf("Number %d: ", i);
        scanf("%d", &v[i]);
    }

    shellsort(v, MAX);

    for(int i=0; i<MAX; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    free(v);
    return 0;
}

void shellsort(int *v, int n)
{
    int gap, i, j, temp;

    for(gap=n/2; gap>0; gap /= 2)
    {
        for(i=gap; i<n; i++)
        {
            for(j=i-gap; j>=0 && v[j]>v[j+gap]; j -= gap)
            {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
        }
    }
}