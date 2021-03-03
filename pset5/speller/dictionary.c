// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a trie
typedef struct node
{
    bool end;
    struct node *next[27];
}
node;

// Number of buckets in trie
const unsigned int N = 27;
// Trie root
node *root;
unsigned int word_counter = 0;

//Returns a new node
node *get_node(void)
{
    node *n = malloc(sizeof(node));
    n->end = false;
    if (n != NULL)
    {
        for (int i = 0; i < N; i++)
        {
            n->next[i] = NULL;
        }
    }
    return n;
}

int get_index(char c)
{
    if (isalpha(c))
    {
        return tolower(c) - 97;
    }
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
    if (root != NULL)
    {
        node *temp = root;
        for (int i = 0; word[i] != '\0'; i++)
        {
            index = get_index(word[i]);
            if (temp->next[index] == NULL)
            {
                return false;
            }
            temp = temp->next[index];
        }
        if (temp->end)
        {
            return true;
        }
    }
    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        char word[LENGTH + 1];
        int index;
        root = get_node();
        if (root == NULL)
        {
            return false;
        }
        node *temp, *nextnode;
        while (fscanf(file, "%s", word) != EOF)
        {
            temp = root;
            for (int i = 0; word[i] != '\0'; i++)
            {
                index = get_index(word[i]);
                if (temp->next[index] == NULL)
                {
                    nextnode = get_node();
                    if (nextnode == NULL)
                    {
                        return false;
                    }
                    temp->next[index] = nextnode;
                }
                temp = temp->next[index];
            }
            temp->end = true;
            word_counter++;
        }
        fclose(file);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_counter;
}

//Recursively remove trie nodes
void freemem(node *trie)
{
    if (trie)
    {
        for (int i = 0; i < N; i++)
        {
            freemem(trie->next[i]);
        }
        free(trie);
    }
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
