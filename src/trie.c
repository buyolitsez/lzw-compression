#include <stdio.h>
#include "trie.h"

static int currIndex = -1;

static int wordSizeBits = ALPHABET_SIZE_BITS + 1;

node_t *create_node(node_t *parent, int wordToParent) {
    node_t *node = (node_t *) malloc(sizeof(node_t));
    assert(node != NULL);
    node->index = currIndex;
    increment_index();
    node->parent = parent;
    node->wordToParent = wordToParent;
    if (parent != NULL) {
        parent->child[wordToParent] = node;
    }
    memset(node->child, 0, sizeof(node_t *) * ALPHABET_SIZE);
    return node;
}

node_t *init() {
    currIndex = -1;
    node_t *root = create_node(NULL, -1);
    //add single character word to dictionary
    fprintf(stderr, "ALPHA - %d\n", ALPHABET_SIZE);
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        create_node(root, i);
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

void increment_index() {
    ++currIndex;
    if ((1 << wordSizeBits) == currIndex) {
        ++wordSizeBits;
    }
    if ((1 << MAX_WORD_SIZE_BITS) == currIndex) { // overflow count of bits
        assert(0); // TODO
    }
}

void decrement_index() {
    --currIndex;
}