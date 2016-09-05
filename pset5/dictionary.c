/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <ctype.h>

#include "dictionary.h"

/**
 * trie to load the dictionary in.
 */
typedef struct _dictionary
{
    bool is_word;
    struct _dictionary *nodes[27];
}
TrieNode;

TrieNode *root;

/**
 * to hold the size of the Trie/Dictionary
 */
unsigned int trieSize = 0;

/**
 * returns the order of the letter in alphabetical order.
 * returns 26 for apostrophe.
 * @param letter
 * @return alphabetical order (0 to 26)
 */
unsigned int getIndex(char letter)
{
    return isalpha(letter) ? ((unsigned int) (tolower(letter) - 'a')) : APOSTROPHE;
}

/**
 * to build the word's path inside the trie.
 * @param node the root node of the Trie.
 * @param index the zero index to iterate over the word.
 * @param word word to be built its path inside the Trie.
 */
bool buildTrie(TrieNode *node, int index, char *const word)
{
    int nodeIndex = getIndex(word[index]);

    // memory allocation for corresponding letter if it's NULL.
    if (node->nodes[nodeIndex] == NULL)
        node->nodes[nodeIndex] = malloc(sizeof(TrieNode));

    node = node->nodes[nodeIndex];

    // If it's the word's last letter, mark it as word.
    if (index == strlen(word) - 1)
    {
        node->is_word = true;
        return true;
    }
    return buildTrie(node, index + 1, word);
}

/**
 * follows the word's path in the Trie, if it exists in the Trie
 */
bool checkWord(TrieNode* const root, int index, const char* word)
{
    TrieNode* node = root;
    int nodeIndex = getIndex(word[index]);

    // sanity check
    if (node->nodes[nodeIndex] == NULL || index > LENGTH)
        return false;

    if (index == strlen(word) - 1)
        return node->nodes[nodeIndex]->is_word;

    return checkWord(node->nodes[nodeIndex], index + 1, word);
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

    return checkWord(root, 0, word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // hold every word from dictionary to save into the trie.
    char word[LENGTH + 1];

    // open the dictionary text file.
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Failed to open the dictionary file!\n");
        return false;
    }

    // initialize the root node.
    root = malloc(sizeof(TrieNode));

    // read words from the dictionary text file.
    while (fscanf(dict, "%s", word) != EOF)
    {
        trieSize++;
        // concatenate newline to the word
        strcat(word, "\0");
        if (!buildTrie(root, 0, word))
            return false;
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return trieSize;
}

/**
 * Unloads dictionary from memory.
 * by freeing all children nodes, then freeing the current node.
 */
void unloadNodes(TrieNode *root)
{
    // free every node from the current node.
    for (int i = 0; i <= APOSTROPHE; i++)
        if (root->nodes[i] != NULL)
            unloadNodes(root->nodes[i]);
    // free the current passed node.
    free(root);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    unloadNodes(root);
    return true;
}
