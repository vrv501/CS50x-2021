#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int isValidKey(string);

int main(int argc, string argv[])
{
    // No definite key is given or too many/less arguments
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    //Key(argv[1]) length is short
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // If duplicate characters/ non-alphabets in the key
    if (isValidKey(argv[1]) == 0)
    {
        printf("Contains duplicate/non alphabets\n");
        return 1;
    }

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
            int index = tolower(character) - 97;

            // Upper cipher character for uppercase letter in plain-text
            if (isupper(character))
            {
                character = toupper(argv[1][index]);
            }

            // Lower cipher character for lowercase letter in plain-text
            else
            {
                character = tolower(argv[1][index]);
            }
        }
        printf("%c", character);
    }
    printf("\n");
    return 0;
}

int isValidKey(string key)
{
    int i;
    int letterCount[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Length: 26
    for (i = 0; i < 26; i++)
    {
        //Check whether character in key is alphabet
        if (isalpha(key[i]))
        {
            int index = tolower(key[i]) - 97;

            // Check if we are seeing the letter for the very first time
            if (letterCount[index] == 0)
            {
                ++letterCount[index];
                continue;
            }
        }
        break;
    }

    //Key is valid
    if (i == 26)
    {
        return 1;
    }

    //Key is Invalid
    return 0;
}
