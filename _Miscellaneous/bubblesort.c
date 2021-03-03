/*
Worst complexity: O(n^2)
Average complexity: Theta(n^2)
Best complexity: Omega(n)
Space complexity: O(1)
Stable, In-place
A sorting algorithm is In-place if the algorithm does not use extra space for manipulating the input but may require a small though nonconstant extra space for its operation.
A sorting algorithm is stable if it does not change the order of elements with the same value.
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    bool sorted = false;
    int a[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(a)/ sizeof(a[0]);
    for (int i = (n - 1); i > 0 && !sorted; i--)
    {
        sorted = true;
        for (int j = 0; j < i; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
                sorted = false;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}