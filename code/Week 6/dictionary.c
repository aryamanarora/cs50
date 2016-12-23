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

#define NUM_BUCKETS 35000

/**
 * global hash table
 */
node* hash_table[NUM_BUCKETS];

/**
 * word count of dictionary
 */
int dict_count = 0;
bool dict_loaded = false;

/**
 * A fancy hash function.
 */
unsigned int hasher(const char* word)
{
    unsigned long hash = 5381;

    for (const char* ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % NUM_BUCKETS;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // lower
    char lower_word[LENGTH+1];
    for (int i = 0; i < LENGTH+1; i++)
        lower_word[i] = tolower(word[i]);

    // get hash
    int hash = hasher(lower_word);

    // initialize cursor
    node* cursor = malloc(sizeof(node));
    cursor = hash_table[hash];

    // traverse linked list
    while (cursor->next != NULL)
    {
        // compare word with current node
        if (strcmp(cursor->word, lower_word) == 0)
        {
            return true;
        }

        // next node
        cursor = cursor->next;
    }

    // if cursor -> next == NULL
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

    // each word, LENGTH + "/0"
    char current_word[LENGTH + 1];

    // set next to NULL in hash table
    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        hash_table[i] = malloc(sizeof(node));
        hash_table[i]->next = NULL;
    }

    // scan dictionary word by word
    while (fscanf(dict, "%s", current_word) != EOF)
    {
        // increment word count
        dict_count++;

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
    dict_loaded = true;

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // if the dictionary was checked, return the word count
    if (dict_loaded == true)
    {
        return dict_count;
    }

    // any other case, return 0
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        node* cursor = hash_table[i];

        while (cursor != NULL)
        {
            node* tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
        free(cursor);
    }
    return true;
}
