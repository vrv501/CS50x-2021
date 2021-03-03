/*
Worst-case performance: O(n)
Average performance: Theta(n/2)
Best-case performance: Omega(1)
Space complexity: O(1)
*/


#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int a[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(a)/ sizeof(a[0]);
    int key = 11;

    for (int i = 0; i < n; i++)
    {
        if (key == a[i])
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not Found\n");
}