// Write a function to replace vowels with numbers

//IMPORTANTTT!!!!
//This is a modified version of the practice problem that takes whole sentences and paragraphs as input or as command line arguments.

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string replace(string word);

int main(int argc, string argv[])
{
    // When user doesn't input commmand line argument
    if (argc == 1)
    {
        string sentences = get_string("Write down the words:\n");
        printf("%s\n", replace(sentences));
    }
    // Repeats the replace function for each command line argument.
    // w starts at 1 to avoid doing the ./code argument.
    else
    {
        for (int w = 1; w < argc; w++)
        {
            printf("%s ", replace(argv[w]));
        }
            printf("\n");
    }
}

string replace(string word)
{
    //loop through letters of word
    for (int i = 0; i < strlen(word); i++)
    {
        switch (word[i])
        {
            case 'a':
                word[i] = '6';
                break;

            case 'e':
                word[i] = '3';
                break;

            case 'i':
                word[i] = '1';
                break;

            case 'o':
                word[i] = '0';
                break;

            default:
                ;
        }
    }
    return word;
}
