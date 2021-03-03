/*
Worst complexity: O(n^2)
Average complexity: Theta(n^2)
Best complexity: Omega(n^2)
Space complexity: O(1)
Not stable, In-Place
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int a[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(a)/ sizeof(a[0]);

    for (int i = 0; i < n; i++)
    {
        int min = a[i], min_ind = i;
        for (int j = (i + 1); j < n; j++)
        {
            if (a[j] < min)
            {
                min = a[j];
                min_ind = j;
            }
        }
        int temp = a[i];
        a[i] = a[min_ind];
        a[min_ind] = temp;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}