#include <stdio.h>
#include <cs50.h>
#include <math.h>

long getPositiveCardNum(void);
int check(long);
void printBrand(long, int);

int main(void)
{
    // Get a cardNumber which is positive long integer
    long cardNumber = getPositiveCardNum();

    // Check if it's a valid credit card number by verifying checksum using Luhn’s algorithm and return it's cardNumberLength
    int cardNumberLength = check(cardNumber);

    // Print the brand of cardNumber
    printBrand(cardNumber, cardNumberLength);
}

long getPositiveCardNum(void)
{
    long cardNumber;
    do
    {
        cardNumber = get_long("Number: "); // cs50 library for accepting an i/p which is long(64-bit integer)
    }
    while (cardNumber <= 0); // Reject any zeros or negative numbers
    return cardNumber;
}

int check(long cardNumber)
{
    int cardNumberLength = 0, checkSum = 0, lastDigit;

    while (cardNumber != 0)
    {
        // Get the last digit from the cardNumber.
        lastDigit = cardNumber % 10;

        // If it's a second-to-last digit in the cardNumber
        if (cardNumberLength % 2 != 0)
        {
            lastDigit = lastDigit * 2;

            // If the above product is a two digit number
            if (lastDigit > 8)
            {
                lastDigit = lastDigit - 9; // Refer Logic 1.1(Bottom of this program) on why we do this
            }
        }

        checkSum = checkSum + lastDigit;
        cardNumber = cardNumber / 10; // Remove the last digit from the cardNumber as it's no longer needed.
        ++cardNumberLength;
    }

    if (checkSum % 10 == 0)
    {
        return cardNumberLength;
    }

    // Return 0 if the checkSum is invalid
    return 0;
}

void printBrand(long cardNumber, int cardNumberLength)
{

    // Check whether cardNumberLength is valid and identify the appropriate brand
    if (cardNumberLength == 13 || cardNumberLength == 15 || cardNumberLength == 16)
    {
        int firstTwoDigits = cardNumber / pow(10, (cardNumberLength - 2));

        // If cardNumberLength is 13 and firstDigit of the cardNumber is 4, it's a VISA card
        if (cardNumberLength == 13)
        {
            if ((firstTwoDigits / 10) == 4) // Simply dividing firstTwoDigits by 10 will get us firstDigit of cardNumber
            {
                printf("VISA\n");
                return;
            }

        }

        // If cardNumberLength is 15, and firstTwoDigits are either 34 or 37, it's a American Express card
        else if (cardNumberLength == 15)
        {
            if (firstTwoDigits == 34 || firstTwoDigits == 37)
            {
                printf("AMEX\n");
                return;
            }
        }

        else if (cardNumberLength == 16)
        {
            // If cardNumberLength is 16 and firstDigit of the cardNumber is 4, it's a VISA card
            if ((firstTwoDigits / 10) == 4)
            {
                printf("VISA\n");
                return;
            }

            // If cardNumberLength is 16 and firstTwoDigits are in range (50 to 56) exclusive, it's a MasterCard card
            else if (firstTwoDigits > 50 && firstTwoDigits < 56)
            {
                printf("MASTERCARD\n");
                return;
            }
        }

    }
    printf("INVALID\n");
}

/*
Logic 1.1: (Operation done to second-to-last digit in Luhn's Algorithm)
0 * 2 = 0
1 * 2 = 2
2 * 2 = 4
3 * 2 = 6
4 * 2 = 8
5 * 2 = 10 = 1 + 0 = 1 (10 - 9)
6 * 2 = 12 = 1 + 2 = 3 (12 - 9)
7 * 2 = 14 = 1 + 4 = 5 (14 - 9)
8 * 2 = 16 = 1 + 6 = 7 (16 - 9)
9 * 2 = 18 = 1 + 8 = 9 (18 - 9)
*/
