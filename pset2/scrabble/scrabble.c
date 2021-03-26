#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        //Check if character is an alphabet
        if (isalpha(word[i]))
        {
            // Convert each letter to lowercase if applicable
            // Then subtract its ascii value with 97 to get an absolute index in range(0 to 25) - [26 alphabets]
            // Use the index to obtain point assigned to that alphabet from POINTS array
            sum += POINTS[(tolower(word[i]) - 97)];
        }
    }
    return sum;
}
