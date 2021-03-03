/*
Worst complexity: O(n*log(n))
Average complexity: Theta(n*log(n))
Best complexity: Omega(n*log(n))
Space complexity: O(n)
Stable, Not In-place
*/
#include <stdio.h>
#include <cs50.h>

void partition(int a[], int low, int high);
void mergeSort(int a[], int low, int mid, int high);

int main(void)
{
    int a[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(a)/ sizeof(a[0]);

    partition(a, 0, (n-1));

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void partition(int a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high)/ 2;
        partition(a, low, mid);
        partition(a, (mid + 1), high);
        mergeSort(a, low, mid, high);
    }
}

void mergeSort(int a[], int low, int mid, int high)
{
    int temp[high - low + 1];
    int i = low, j = mid + 1, k = low;
    while((i <= mid) && (j <= high))
    {
        if(a[i] < a[j])
        {
            temp[k] = a[i];
            ++i;
        }
        else
        {
            temp[k] = a[j];
            ++j;
        }
        ++k;
    }
    while (i <= mid)
    {
        temp[k] = a[i];
        ++k;
        ++i;
    }

	while (j <= high)
	{
	    temp[k] = a[j];
        ++k;
        ++j;
	}

	for (i= low; i <= high ; i++)
	{
	    a[i]=temp[i];
	}

}