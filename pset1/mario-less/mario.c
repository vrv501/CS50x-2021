#include <stdio.h>
#include <cs50.h>

int getPositiveNum(void);
void printPyramid(int);
void printPadding(int, int);
void printHash(int);

int main(void)
{
    // Get a positive integer from user
    int height = getPositiveNum();

    // Print the pyramid
    printPyramid(height);
}

int getPositiveNum(void)
{
    int num;
    do
    {
        num = get_int("Height: ");
    }
    while (num <= 0 || num > 8); // Reject if the number is less than or equal to 0, or greater than 8
    return num;
}

void printPyramid(int height)
{
    for (int row = 0; row < height; row++)
    {
        // Padding
        printPadding(height, row);

        //Print #
        printHash(row);

        printf("\n");
    }
}

void printPadding(int height, int row)
{
    for (int col = 0; col < (height - row - 1); col++)
    {
        printf(" ");
    }
}


void printHash(int row)
{
    for (int count = 0; count < (row + 1); count++)
    {
        printf("#");
    }
}
