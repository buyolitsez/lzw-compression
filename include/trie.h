#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 27

typedef struct node {
    int index;
    struct node *child[ALPHABET_SIZE];
} node_t;

node_t *create_node();

node_t *init();

#endif //TRIE_H
