// Implements a dictionary's functionality
// WEEK 5

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26 * 26;

// Hash table
node *table[N];

// own function to recursively free nodes in list
void free_nodes(node *head);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int code = hash(word);
    node *trav = table[code];

    // while there is a node
    while (trav != NULL)
    {
        // if word match
        if (strcasecmp(word, trav->word) == 0)
        {
            // found word
            return true;
        }

        // else, go to next
        trav = trav->next;
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{

    int code = 0;
    int length = strlen(word);

    // FUNCTION 1 (0.14s avg total lalaland.txt)
    // Functions takes the values for the first, second, and third letters in a word. ( considers order, meaning aab and baa are not the same ( aab is code 1, baa is code 26 * 26 ))
    /*
    if (length >= 3)
    {
        code = (26 * 26) * (tolower(word[0]) - 'a') + (26) * (tolower(word[1]) - 'a') + (tolower(word[2]) - 'a');
    }
    // 2 Letter words
    else if (length == 2)
    {
        code = (26 * 26) * (tolower(word[0]) - 'a') + (26) * (tolower(word[1]) - 'a');
    }
    // 1 letter words
    else
    {
        code = (26 * 26) * (tolower(word[0]) - 'a');
    }

    //-- Possble optimizations for later.
    if (code < 0)
    {
        code = 0;
    }
    else if (code >= N)
    {
        code = N - 1;
    }
    return code;
    */

    // FUNCTION 2 (0.07s avg total lalaland.txt)
    // uses first 4 chars, and almost almost equals the staffs solution in speed, but uses a ton of memory. about 95mb just for the table array.
    unsigned int factor = N / 26;
    int i = 0;
    while (word[i] != '\0' && factor != 0)
    {
        code += factor * (tolower(word[i]) - 'a');
        factor /= 26;
        i++;
    }
    return code;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // initialise pointers in table[N] to null.
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // open dictionary
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        return false;
    }

    // temporary buffer node for copying words
    node *buffer_node = malloc(sizeof(node));
    buffer_node->next = NULL;

    if (buffer_node == NULL)
    {
        fclose(dict_file);
        return false;
    }

    // loop through all words in dictionary (method taken from week 5 practise problem trie)
    while (fscanf(dict_file, "%s", buffer_node->word) == 1)
    {

        // get index of word
        int code = hash(buffer_node->word);

        // Not first node in list at table[code]
        if (table[code] != NULL)
        {
            // pointer for traversal in list
            node *trav = table[code];

            // while trav doesn't point at last node in list
            while (trav->next != NULL)
            {
                // set trav as pointer to next node
                trav = trav->next;
            }

            // Now, trav points at last node, so add the new node.
            trav->next = buffer_node;
        }

        else
        {
            table[code] = buffer_node;
        }
        // new memory for next node. (will be freed if not used.)
        buffer_node = malloc(sizeof(node));
        buffer_node->next = NULL;

        if (buffer_node == NULL)
        {
            fclose(dict_file);
            // Unload current words from memory.
            unload();
            return false;
        }
    }


    // frees the temporary pointers used.
    free(buffer_node);
    fclose(dict_file);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int word_count = 0;
    node *trav = NULL;

    for (int i = 0; i < N; i++)
    {
        trav = table[i];
        while (trav != NULL)
        {
            trav = trav->next;
            word_count++;
        }
    }
    return word_count;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through lists
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            // if failed to free
            free_nodes(table[i]);
        }
    }
    return true;
}

void free_nodes(node *head)
{
    // base case
    if (head == NULL)
    {
        return;
    }
    else
    {
        // free rest of linked nodes first
        free_nodes(head->next);
    }
    // free self
    free(head);
}
