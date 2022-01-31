#include "trie.h"

static int cur_index = -1;

node_t *create_node() {
    node_t *node = malloc(sizeof(node_t));
    node->index = cur_index++;
    memset(node->child, 0, sizeof(node_t *) * ALPHABET_SIZE);
    return node;
}

node_t *init() {
    cur_index = -1;
    node_t *root = create_node();
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        root->child[i] = create_node();
    }
    return root;
}
