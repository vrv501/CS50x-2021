#include <stdio.h>
#include <cs50.h>
#include <math.h>

long get_positive_num(void);
void check(long);

int main(void)
{
    long number = get_positive_num(); //get a valid long int
    check(number); //check if it's a valid credit card number
}

long get_positive_num(void)
{
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n <= 0);
    return n;
}

void check(long num)
{
    int length = 0, even_sum = 0, odd_sum = 0, rem, odd_rem;
    long copy_num = num;
    //The below loop calculates length and checksum of given number
    while (num != 0)
    {
        rem = num % 10;

        //Calculate the sum when number is multiplied by 2 when we aare adding second-to-last digits
        if (rem < 5)
        {
            odd_rem = rem * 2;
        }
        else
        {
            odd_rem = (2 * rem) - 9;
        }

        even_sum = even_sum + (rem * ((1 + length) % 2));
        odd_sum = odd_sum + (odd_rem * (length % 2));
        num = num / 10;
        ++length;
    }
    //Check whether length and checksum are valid and identify appropriate credit card name
    if (length > 12 && length < 17 && (odd_sum + even_sum) % 10 == 0)
    {
        int first_two = copy_num / pow(10, (length - 2));
        if (length == 13)
        {
            if ((first_two / 10) == 4)
            {
                printf("VISA\n");            //If length is 13 and first number is 4, it's a VISA card
                return;
            }

        }
        else if (length == 15)
        {
            if (first_two == 34 || first_two == 37)
            {
                printf("AMEX\n");  //If length is 15, and first number is 34 or 37, it's a American Express card
                return;
            }
        }
        else if (length == 16)
        {
            if ((first_two / 10) == 4)
            {
                printf("VISA\n"); //If length is 16 and first number is 4, it's a VISA card
                return;
            }
            else if (first_two > 50 && first_two < 56)
            {
                printf("MASTERCARD\n"); //If length is 16 and first number is in range (51,56), it's a MasterCard card
                return;
            }
        }

    }
    printf("INVALID\n");


}