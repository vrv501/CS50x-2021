#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    float letters = 0, sentences = 0, words = 0;
    int i, length = strlen(text);

    // Iterate through every character to count letters, words, sentences
    for (i = 0; i < length && words <= 100; i++)
    {

        // The character is a letter
        if (tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z')
        {
            ++letters;
        }

        // The character is a white space
        else if (text[i] == ' ')
        {
            ++words;
        }

        // The character is a question, exclamation mark or period
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            ++sentences;
        }

        // Don't bother otherwise
        else
        {
            continue;
        }
    }

    // If we have reached the end of text, then add the last word to wordCount since it doesn't end with '.', '!', '?'
    if (i == length)
    {
        ++words;
    }

    // If words < 100, count the avg number of letters and sentences per 100 words
    if (words < 100)
    {
        letters = (letters * 100.0) / words;
        sentences = (sentences * 100.0) / words;
    }

    // Coleman-Liau index for grade calculation
    int index = round((0.0588 * letters) - (0.296 * sentences) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index > 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }

}
