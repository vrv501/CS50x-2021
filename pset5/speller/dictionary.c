// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a trie
typedef struct trie
{
    bool endOfword;
    struct trie *next[27];
} trie;

void freemem(trie *);

// Number of buckets in trie
const unsigned int N = 27;

// Trie root
trie *root;
unsigned int word_counter = 0;

// Returns a new node
trie *get_node(void)
{
    trie *node = malloc(sizeof(trie));
    node->endOfword = false;

    if (node != NULL)
    {
        for (int i = 0; i < N; i++)
        {
            node->next[i] = NULL;
        }
    }
    return node;
}

int get_index(char character)
{
    // If character is alphabet, return alphabet position [0 to 25]
    if (isalpha(character))
    {
        return tolower(character) - 97;
    }

    // If not just return 26
    else
    {
        return 26;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int index;
    if (root == NULL)
    {
        return false;
    }

    trie *temp = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        index = get_index(word[i]);

        // If the next node is NULL, the word isn't in dictionary
        if (temp->next[index] == NULL)
        {
            return false;
        }
        temp = temp->next[index];
    }

    // If end of node is true, then we have found the word in dictionary
    if (temp->endOfword)
    {
        return true;
    }
    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    root = get_node();
    if (root == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    int index;
    trie *temp, *nextnode;
    while (fscanf(file, "%s", word) != EOF)
    {
        temp = root;
        for (int i = 0; word[i] != '\0'; i++)
        {
            index = get_index(word[i]);

            // If the next node is Null then attach a new node
            if (temp->next[index] == NULL)
            {
                nextnode = get_node();
                if (nextnode == NULL)
                {
                    return false;
                }
                temp->next[index] = nextnode;
            }

            // If next node isn't NULL, then we move down the trie
            temp = temp->next[index];
        }

        temp->endOfword = true;
        word_counter++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (root != NULL)
    {
        for (int i = 0; i < N; i++)
        {
            freemem(root->next[i]);
        }
        free(root);
        return true;
    }

    return false;
}

//Recursively remove trie nodes
void freemem(trie *node)
{
    if (node)
    {
        for (int i = 0; i < N; i++)
        {
            freemem(node->next[i]);
        }
        free(node);
    }
}
