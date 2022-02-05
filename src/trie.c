#include <stdio.h>
#include "trie.h"

static int currIndex = -1;

static int wordSizeBits = ALPHABET_SIZE_BITS + 1;

bool create_node(node_t **root, node_t *parent, int wordToParent, node_t **newNode) {
    node_t *node = (node_t *) malloc(sizeof(node_t));
    assert(node != NULL);
    node->index = currIndex;
    bool wasReset = increment_index(root);
    if (wasReset) {
        return true;
        node->index = currIndex;
    }
    node->parent = parent;
    node->wordToParent = wordToParent;
    if (parent != NULL) {
        parent->child[wordToParent] = node;
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        node->child[i] = NULL;
    }
//    memset(node->child, 0, sizeof(node_t *) * ALPHABET_SIZE);
    *newNode = node;
    return wasReset;
}

node_t *init() {
    currIndex = -1;
    wordSizeBits = ALPHABET_SIZE_BITS + 1;
    node_t *root;
    create_node(NULL, NULL, -1, &root);
    //add single character word to dictionary
    fprintf(stderr, "ALPHA - %d\n", ALPHABET_SIZE);
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        node_t *res;
        create_node(&root, root, i, &res);
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

int get_curr_index() {
    return currIndex;
}

bool increment_index(node_t **root) {
    ++currIndex;
    while ((1 << wordSizeBits) <= currIndex) {
        ++wordSizeBits;
    }
    bool wasReset = false;
    if (MAX_WORD_SIZE_BITS == wordSizeBits) { // overflow count of bits
        delete_trie(*root);
        (*root) = init();
        wasReset = true;
    }
    return wasReset;
}

void decrement_index() {
    --currIndex;
}