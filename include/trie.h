#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "constants.h"

typedef struct node {
    int index;
    int wordToParent;
    struct node *parent;
    struct node *child[ALPHABET_SIZE];
} node_t;

bool create_node(node_t **root, node_t *parent, int wordToParent, node_t **newNode);

node_t *init();

void delete_trie(node_t *root);

int get_word_size_bits();

int get_curr_index();

bool increment_index(node_t **root);

void decrement_index();

#endif //TRIE_H
