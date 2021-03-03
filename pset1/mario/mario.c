#include <stdio.h>
#include <cs50.h>

int get_positive_num(void);
void print_half(int i);

int main(void)
{
    int n = get_positive_num(); //User Height input

    for (int i = 1; i <= n; i++)            //Print the ladder
    {
        for (int j = 1; j <= (n - i); j++)  //Padding
        {
            printf(" ");
        }
        print_half(i); //Left Half
        printf("  ");
        print_half(i); //Right Half
        printf("\n");
    }
}

int get_positive_num(void) //Check for valid user input
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n <= 0 || n > 8);
    return n;
}

void print_half(int i)
{
    for (int j = 1; j <= i; j++)
    {
        printf("#");
    }
}