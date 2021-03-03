/*
Worst complexity: O(n^2)
Average complexity: Theta(n^2)
Best complexity: Omega(n)
Space complexity: O(1)
Stable, In-place
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int a[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(a)/ sizeof(a[0]), j;

    for (int i = 1; i < n; i++)
    {
        int temp = a[i];
        for (j = (i - 1); j >= 0; j--)
        {
            if (a[j] > temp)
            {
                a[j + 1] = a[j];
            }
            else
            {
                break;
            }
        }
        a[++j] = temp;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}