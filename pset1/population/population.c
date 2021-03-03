#include <cs50.h>
#include <stdio.h>

int get_start_int(void);
int get_end_int(int);

int main(void)
{
    int start_size = get_start_int(); //starting year
    int end_size = get_end_int(start_size); //ending year
    int years = 0;
    while (start_size < end_size)
    {
        start_size = start_size + (start_size / 3) - (start_size / 4);
        years++;
    }
    printf("Years: %d\n", years); //total number of years taken
}

int get_start_int(void)
{
    int n;
    do
    {
        n = get_int("Start size: "); //Get input from User
    }
    while (n < 9);
    return n;
}
int get_end_int(int start_size)
{
    int n;
    do
    {
        n = get_int("End size: ");//Get input from User
    }
    while (n < start_size);
    return n;
}