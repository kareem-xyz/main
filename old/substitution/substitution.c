#include <cs50.h>
#include <stdio.h>
// below libraries are from cs50 manual pages
#include <string.h>
#include <ctype.h>

bool check_key(string key);
void cipher_word(string word, string key);

#define key_length 26
int main(int argc, string argv[])
{
    string key = argv[1];
    //strcpy(argv[1], key);

    // checking for correct usage.
    if (argc != 2)
    {
        printf("ERORR: Usage ./substitution key\n");
        return 1;
    }
    // function checks if key is correct.
    if (!check_key(key))
    {
        return 1;
    }
    // get the users input.
    string word = get_string("plaintext:");

    // cipher and print.
    cipher_word(word, key);
    return 0;
}

// checks whether the key is correct
bool check_key(string key)

{
    if (strlen(key) != key_length)
    {
        printf("ERORR: Key must be 26 charcters.\n");
        return false;
    }
    // if a key is duplicated
    for (int i = 0; i < key_length; i++)
    {
        // if it's not alphabetical.
        if (!isalpha(key[i]))
        {
            printf("ERORR: Key must be alphabetical.");
            return false;
        }
        for (int j = 0; j < key_length; j++)
        {
            // if its the same letter in the same spot, skip
            if (i == j)
            {
                continue;
            }
            // if the letter is repeated.
            if (key[i] == key[j])
            {
                printf("ERORR: cannot use the same letter more than once. The letter %c occurs twice as no.%i and no.%i", key[i], i, j);
                return false;
            }
        }

    }
    // if the key passed the three checks above, then its correct.
    return true;
}

void cipher_word(string word, string key)
{
    printf("ciphertext: ");
    // loop through word,
    for (int i = 0; i < strlen(word); i++)
    {
        // if the character isnt alphabetical print it as it is.
        int index;
        if (!isalpha(word[i]))
        {
            printf("%c", word[i]);
            continue;
        }
        // if uppercase , find its index in the alphabet and print from key.
        if (isupper(word[i]))
        {
            index = word[i] - 'A';
            printf("%c", toupper(key[index]));
            continue;
        }
        // if lower do the same as upper but for lowercase.
        else
        {
            index = word[i] - 'a';
            printf("%c", tolower(key[index]));
            continue;
        }
    }
    printf("\n");
}