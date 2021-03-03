#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: "); //Get the input from user
    int letters = 0, sentences = 0, words = 0, i, length = strlen(text);
    float L, S;
    for (i = 0; i < length && words <= 100; i++)                                      //In this loop we count sentences, words, letters
    {
        if (tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z')          //The character is a letter
        {
            ++letters;
        }
        else if (text[i] == ' ')        //The character is a white space
        {
            ++words;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')             //The character is a question, exclamation mark or period
        {
            ++sentences;
        }
        else
        {
            continue;
        }
    }
    if (i == length)
    {
        ++words; //Count last word if we are finished and at the end of sentence
    }
    L = letters;
    S = sentences;
    if (words < 100)
    {
        L = (L * 100) / words; //If words < 100, count the avg number of letters and sentences per 100 words
        S = (S * 100) / words;
    }
    int index = round((0.0588 * L) - (0.296 * S) - 15.8); //Coleman-Liau index for grade calculation
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