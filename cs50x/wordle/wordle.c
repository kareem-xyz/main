// WORDLE GAME
// still needs some work since the coloring for uncorrectly placed letters is still falwed in my opinion.

#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    // TODO #1
    if (argc != 2)
    {
        printf(RED"ERORR:"RESET" Please input a number between 5 and 8 as command-line-argumennt\n");
        return 1;
    }
    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    // atoi converts string to int
    // TODO #2
    int k = atoi(argv[1]);
    if (k > 8 || k < 5)
    {
        printf("ERROR:"RESET" Input one command-line-argument please.\n");
        return 1;
    }
    int wordsize = k;


    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];
        // set all elements of status array initially to 0, aka WRONG (Because it will change with each guess)
        // TODO #4
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = WRONG;
        }
        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }
    // Print the game's result
    // TODO #7
    if (won)
    {
        printf(GREEN"CONGRATULATIONS!!!"RESET"\n YOU WON!\n");
    }
    else
    {
        printf(RED"SORRY!!"RESET" MAYBE THIS IS JUST TOO HARD FOR YOU\n TRY AGAIN LATER\nThe word was"GREEN"%s"RESET"\n", choice);
    }
    // that's all folks!
    return 0;
}


string get_guess(int wordsize)
{
    // ensure users actually provide a guess that is the correct length
    string guess;
    int len;
    do
    {
        guess = get_string("Input a %i-letter word:", wordsize);
        len = strlen(guess);
    }
    while (len != wordsize);
    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    // iterate over each letter of the guess
    for (int i = 0; i < wordsize; i++)
    {
        // iterate over each letter of the choice
        for (int j = 0; j < wordsize; j++)
        {
            // compare the current guess letter to the current choice letter
            // if they're the same position in the word, score EXACT points (green)
            // (i = j) means same position
            if (guess[i] == choice[j] && i == j)
            {
                score += EXACT;
                // its worth noting that arrays in c are passed not by value, so changing them here changes it in main aswell.
                status [i] = EXACT;
            }
        }
    }

    for (int i = 0; i < wordsize; i++)
    {
        for (int j = 0; j < wordsize; j++)
        {
            // if it's in the word, but not the right spot, score CLOSE point (yellow)
            if (guess [i] == choice[j] && status[j] != EXACT)
            {
                score += CLOSE;
                status[i] = CLOSE;
            }
        }

    }
    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    for (int i = 0; i < wordsize; i++)
    {
        // Checks score of value from array status
        if (status[i] == 2)
        {
            printf(GREEN"%c"RESET"", guess[i]);
        }
        else if (status[i] == 1)
        {
            printf(YELLOW"%c"RESET"", guess[i]);
        }
        else
        {
            printf(RED"%c"RESET"", guess[i]);
        }
    }
    printf("\n");
    return;
}
