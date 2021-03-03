/*
Worst Case Complexity: O(n^2)
Average Case Complexity: Theta(n*log n)
Best Case Complexity: Omega(n*log n)
Space complexity: O(n)
Not stable, In-place
*/

#include <stdio.h>
#include <cs50.h>

void quicksort(int a[], int p, int r);

int main(void)
{
    int a[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(a)/ sizeof(a[0]);

    quicksort(a, 0, (n-1));

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];  // selecting last element as pivot
    int i = (low - 1);  // index of smaller element

    for (int j = low; j < high; j++)
    {
        // If the current element is smaller than or equal to pivot
        if (arr[j] < pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quicksort(int a[], int low, int high)
{
    int q;
    if(low < high)
    {
        q = partition(a, low, high);
        quicksort(a, low, q-1);
        quicksort(a, q+1, high);
    }
}