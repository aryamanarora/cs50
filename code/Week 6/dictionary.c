/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

/**
 * define node struct for a hash table
 */
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

int hasher(char word[])
{
    // lower case
    char letter_to_hash = tolower(word[0]);

    // time to hash!
    int hash;
    if (isalpha(letter_to_hash))
        hash = (letter_to_hash - 'a') + 1;
    else
        hash = 0;

    // gimme the hash
    return hash;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // read the dictionary
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }

    // make the root nodes
    node* hash_table[26];

    // each word, LENGTH + "/0"
    char current_word[LENGTH + 1];

    // scan dictionary word by word
    while (fscanf(dict, "%s", current_word) != EOF)
    {
        // make new node for word
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Unable to begin loading\n");
            return false;
        }

        // hash
        int hash = hasher(current_word);

        // add word to node
        strcpy(new_node->word, current_word);

        // move node to correct place
        new_node->next = hash_table[hash];
        hash_table[hash] = new_node;
    }

    // that's all folks
    fclose(dict);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
