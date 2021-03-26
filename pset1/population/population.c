#include <cs50.h>
#include <stdio.h>

int getStartSize(void);
int getEndSize(int);

int main(void)
{
    // Get starting population size
    int startSize = getStartSize();

    // Get ending population size
    int endSize = getEndSize(startSize);
    
    // Time taken to go from startSize to endSize
    int years = 0;
    while (startSize < endSize)
    {
        startSize = startSize + (startSize / 3) - (startSize / 4);
        ++years;
    }
    printf("Years: %d\n", years);
}

int getStartSize(void)
{
    int num;
    do
    {
        num = get_int("Start size: ");
    }
    while (num < 9); // Reject any number less than 9(min start population size limit)
    return num;
}

int getEndSize(int startSize)
{
    int num;
    do
    {
        num = get_int("End size: ");
    }
    while (num < startSize); //Reject any number that is less than startSize
    return num;
}
