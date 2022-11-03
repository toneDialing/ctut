#include <stdio.h>

/* qsort: sort v[left], ..., v[right] into increasing order */

void qsort(int *v, int left, int right);
void swap(int *v, int i, int j);

int main(void)
{
    int v[] = {87, 14, 19, 37, 6, 22, 104, 58, 32}; //lazy hardcoding to demonstrate qsort

    qsort(v, 0, 8);
    
    for(int i=0; i<=8; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}

void qsort(int *v, int left, int right)
{
    int i, last;

    if(left>=right)
    {
        return;
    }
    swap(v, left, (left+right)/2);
    last = left;

    for(i=left+1; i<=right; i++)
    {
        if(v[i]<v[left])
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(int *v, int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}