#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

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
    int d = score1 - score2;
    if (d > 0)
    {
        printf("Player 1 wins!\n");
    }
    else if (d < 0)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

}

int compute_score(string word)
{
    int score = 0;
    // Goes through each charcter in the string
    // Could've used the method for searching for NUL \0 but this is cleaner
    for (int i = 0; i < strlen(word); i++)
    {
        // Checks whether charcter is alphabetical, otherwise ignores
        // Could've said if(word[i] >=65 && word[i] <= 90) because 90 is Z
        // Function is in CS50 Manual
        if (isalpha(word[i]))
        {

            //Converts each charcter to uppercase, get its integer from ascii. and call it c
            int c = toupper(word[i]);

            // Order of letter from points array is [c - 65] (because 65 is capital A)
            // Adds letter points to score
            score += POINTS[c - 65];
        }

    }
    return score;
}
