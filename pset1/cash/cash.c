#include <stdio.h>
#include <cs50.h>
#include <math.h>

int getChange(void);
void printCoins(int);

int main(void)
{
    // Get change from user
    int penny = getChange();

    // Print the number of coins required for change
    printCoins(penny);
}

int getChange(void)
{
    float change;
    do
    {
        change = get_float("Change owed: "); // cs50 library for accepting an i/p which is float(32-bit decimal number)
    }
    while (change <= 0); // Reject any zeros or negative numbers
    return round(100 * change);
}

void printCoins(int penny)
{
    int cents25, cents10, cents5, cents1, totalCoins;

    // Number of 25 cent coins required
    cents25 = penny / 25;
    penny = penny - (cents25 * 25);

    // Number of 10 cent coins required
    cents10 = penny / 10;
    penny = penny - (cents10 * 10);

    // Number of 5 cent coins required
    cents5 = penny / 5;
    penny = penny - (cents5 * 5);

    // Number of 1 cent coins required
    cents1 = penny;

    totalCoins = cents25 + cents10 + cents5 + cents1;
    printf("%d\n", totalCoins);
}
