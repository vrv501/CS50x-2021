#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // No definite key is given or too many/less arguments
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Key is not an integer
    int flag = 0;
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Valid key and arguments provided
    printf("Success\n");

    // Convert string key into an integer
    int key = atoi(argv[1]);

    // Get input from user
    string plaintext = get_string("plaintext: ");
    int length = strlen(plaintext);
    char character;

    // Print the cipher text using key for plain-text
    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        character = plaintext[i];
        if (isalpha(character))
        {
            // Convert letter to lowercase if applicable
            // Then subtract its ascii value with 97 to get an absolute index in range(0 to 25) - [26 alphabets]
            int alphabetPosition = tolower(character) - 97;

            // Get the position of letter after rotating argv[1] times (Caesar’s algorithm)
            alphabetPosition = (alphabetPosition + key) % 26;

            // Upper cipher character for uppercase letter in plain-text
            if (isupper(character))
            {
                alphabetPosition = alphabetPosition + 65;
                character = (char)alphabetPosition;
            }

            // Lower cipher character for lowercase letter in plain-text
            else
            {
                alphabetPosition = alphabetPosition + 97;
                character = (char)alphabetPosition;
            }
        }
        printf("%c", character);
    }
    printf("\n");
    return 0;
}
