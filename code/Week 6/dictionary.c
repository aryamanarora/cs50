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

/**
 * My very own fancy hash function.
 */
int hash_function(node* word)
{
    return ((int) word->word[0]) - 97;
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
    // node* name = malloc(sizeof(node));
    // name->word = "word";

    // open the file
    FILE* dict = fopen(dictionary, "w");

    // handle NULL files
    if (dict == NULL)
    {
        return false;
    }

    // hashtable, A-Z
    node* hashtable[26];

    // load file into hashtable
    while (!feof(dict))
    {
        // scan new word
        node* new_word = malloc(sizeof(node));
        fscanf(dict, "%s", new_word->word);

        // get hash
        int hash = hash_function(new_word);

        // add to correct bin
        new_word->next = hashtable[hash];
        hashtable[hash] = new_word;
    }

    return false;
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
