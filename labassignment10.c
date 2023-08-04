#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For tolower function

// Trie node structure
struct TrieNode {
    struct TrieNode* children[26];
    int count; // Number of occurrences of the word
};

// Trie structure
struct Trie {
    struct TrieNode* root;
};

// Creates a new TrieNode
struct TrieNode* createTrieNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode) {
        for (int i = 0; i < 26; i++) {
            newNode->children[i] = NULL;
        }
        newNode->count = 0;
    }
    return newNode;
}

// Initializes a trie structure
struct Trie* createTrie() {
    struct Trie* newTrie = (struct Trie*)malloc(sizeof(struct Trie));
    if (newTrie) {
        newTrie->root = createTrieNode();
    }
    return newTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word) {
    if (!pTrie || !word) return;

    struct TrieNode* currentNode = pTrie->root;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = tolower(word[i]) - 'a'; // Convert the character to lowercase
        if (index < 0 || index >= 26) {
            // Ignore non-alphabetic characters
            continue;
        }
        if (!currentNode->children[index]) {
            currentNode->children[index] = createTrieNode();
        }
        currentNode = currentNode->children[index];
    }

    currentNode->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie* pTrie, char* word) {
    if (!pTrie || !word) return 0;

    struct TrieNode* currentNode = pTrie->root;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = tolower(word[i]) - 'a'; // Convert the character to lowercase
        if (index < 0 || index >= 26 || !currentNode->children[index]) {
            // The word or character does not exist in the trie
            return 0;
        }
        currentNode = currentNode->children[index];
    }

    return currentNode->count;
}

// Helper function to deallocate the trie nodes recursively
void deallocateTrieHelper(struct TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) {
        deallocateTrieHelper(node->children[i]);
    }
    free(node);
}

// Deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (!pTrie) return NULL;
    deallocateTrieHelper(pTrie->root);
    free(pTrie);
    return NULL;
}

// This function will return the number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }

    int numWords = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp) && numWords < 256) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; // Remove the newline character
        }
        pInWords[numWords] = strdup(buffer);
        numWords++;
    }

    fclose(fp);
    return numWords;
}

int main(void) {
    char* inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    struct Trie* pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
        insert(pTrie, inWords[i]);
    }

    // Test the occurrences of words
    char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");

    // Free the memory used for reading dictionary words
    for (int i = 0; i < numWords; i++) {
        free(inWords[i]);
    }

    return 0;
}
