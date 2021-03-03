#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int isValid(string);
int main(int argc, string argv[])
{
    if (argc == 2)
    {
        if (strlen(argv[1]) == 26)
        {
            if (isValid(argv[1]))
            {
                string plaintext = get_string("plaintext: ");    //User input
                int length = strlen(plaintext);
                char character;
                printf("ciphertext: ");
                for (int i = 0; i < length; i++)
                {
                    character = tolower(plaintext[i]);
                    if (character >= 'a' && character <= 'z')
                    {
                        character = tolower(argv[1][(character - 97)]);  //Get the index of plaintext in key
                        if (isupper(plaintext[i]))
                        {
                            character = toupper(character);      //If it's a upper case letter, convert accordlingly
                        }
                    }
                    printf("%c", character);          //print the letter
                }
                printf("\n");
                return 0;
            }
            else
            {
                printf("Contains duplicate/non alphabets\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");           //Key length is short
            return 1;
        }
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);         //No definite key is given or too many/less arguments
        return 1;
    }
}


int isValid(string key)
{
    int i;
    int key1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (i = 0; i < 26; i++)
    {
        if (isalpha(key[i]))                       //Check whether character in key is alphabet
        {
            int index = tolower(key[i]) - 97;
            if (key1[index] == 0)              //Test frequency is singular
            {
                ++key1[index];
                continue;
            }
        }
        break;
    }
    if (i == 26)            //Key is valid
    {
        return 1;
    }
    else                   //Key is Invalid
    {
        return 0;
    }
}