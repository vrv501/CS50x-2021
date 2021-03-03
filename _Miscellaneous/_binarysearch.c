/*
Worst complexity: O(log n)
Average complexity: Theta(log n)
Best complexity: Omega(1)
Space complexity: O(1)
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int a[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(a)/ sizeof(a[0]);
    int key = 100;
    int low = 0, high = (n - 1);
    while (low <= high)
    {
         int mid = (low + high)/ 2;
         if (key == a[mid])
         {
             printf("Found\n");
             return 0;
         }
         else if(key < a[mid])
         {
             high = mid - 1;
         }
         else
         {
             low = mid + 1;
         }
    }
    printf("Not Found\n");

}