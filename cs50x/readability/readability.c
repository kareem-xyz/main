// Program to grade level a text.
// Could be More efficient by combining the functions into one function that would scan the text only--
// -- once and return all values. Cs50 implementaion requires there to be 3 functions ,however, so I did so.

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//All functions take the text and its length
int noletters(string t, int l);
int nowords(string t, int l);
int nosents(string t, int l);


int main(void)
{
    // Get string of text
    string text = get_string("Write text:\n");

    // Get length of string
    int length = strlen(text);

    // calculate number of sentences (punct marks
    //uses number of words to add the words at the end of a sentence
    int sents = nosents(text, length);

    // calculate number of words (number of blank spaces + 1 because of last word in last sentence won't have a space after it )
    int words = nowords(text, length);

    // Calculate number of letters
    int letters = noletters(text, length);

    // Sugar of Programing
    if (letters == 0 || sents == 0 || words == 0)
    {
        printf("ERORR: Please make sure your write at least one word, and use punctuation marks\n");
        return 1;
    }

    // Calculate average of letters per 100 words in text (L)
    float L = (float)letters / words * 100;

    // Calculate average of sentences per 100 words.
    float S = (float)sents / words * 100;

    // Apply and print the index number rounded
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 16 && index >= 1)
    {
        printf("Grade %i\n", index);
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Something went wrong!\n");
        return 1;
    }

}

//FUNCTIONS:------
//Calculates number of letters in a text
int noletters(string t, int l)
{
    int letters = 0;
    for (int i = 0; i < l; i++)
    {
        if (isalpha(t[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Calculates the number of words in a text
int nowords(string t, int l)
{
    int words = 0;
    for (int i = 0; i < l; i++)
    {
        if (isspace(t[i]))
        {
            words++;
        }
    }
    // Last word in text (because it has only a punct mark after it and no space) wont be recorded, so we add 1
    return words + 1;
}

//Calculates number of sentences in a text.
int nosents(string t, int l)
{
    int sents = 0;
    for (int i = 0; i < l; i++)
    {
        if (t[i] == '.' || t[i] == '?' || t[i] == '!')
        {
            sents++;
        }
    }
    return sents;
}

