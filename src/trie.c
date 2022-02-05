#include <stdio.h>
#include "trie.h"

static int currIndex = -1;

static int wordSizeBits = ALPHABET_SIZE_BITS + 1;

extern inline void* mymalloc(ssize_t size);

node_t* create_node(node_t **root, node_t *parent, int wordToParent) {
    node_t *node = (node_t *) mymalloc(sizeof(node_t));
    node->index = currIndex;
    increment_index(root);
    node->parent = parent;
    node->wordToParent = wordToParent;
    if (parent != NULL)
        parent->child[wordToParent] = node;
    memset(node->child, 0, sizeof(node_t *) * ALPHABET_SIZE);
    return node;
}

node_t* init() {
    currIndex = -1; // root has index -1
    wordSizeBits = ALPHABET_SIZE_BITS + 1;
    node_t *root = create_node(NULL, NULL, -1);
    for (int i = 0; i < ALPHABET_SIZE; ++i) { // add single character word to dictionary
        create_node(&root, root, i);
    }
    currIndex += 2; // for CLC and EOI
    return root;
}

void delete_trie(node_t *root) {
    if (root != NULL) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            delete_trie(root->child[i]);
        }
        free(root);
    }
}

int get_word_size_bits() {
    return wordSizeBits;
}

bool increment_index(node_t **root) {
    ++currIndex;
    while ((1 << wordSizeBits) <= currIndex) {
        ++wordSizeBits;
    }
    if (MAX_WORD_SIZE_BITS <= wordSizeBits) { // overflow count of bits
        delete_trie(*root);
        (*root) = init();
        return true;
    }
    return false;
}

void decrement_index() {
    --currIndex;
}