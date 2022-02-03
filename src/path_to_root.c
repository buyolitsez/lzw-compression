#include "path_to_root.h"

static int buffer[1024];
int cnt = 0;

void flush_path_buffer(FILE *stream) {
    while (cnt) {
        write_to_file(buffer[--cnt], ALPHABET_SIZE_BITS, stream);
    }
}

void write_path_to_root_reversed(node_t *node) {
    node_t *currNode = node;
    assert(currNode != NULL);
    while (currNode->index != -1) { // while not root
        buffer[cnt++] = currNode->wordToParent;
        currNode = currNode->parent;
    }
}

int get_first_element(node_t *node) {
    write_path_to_root_reversed(node);
    int answer = buffer[cnt - 1];
    cnt = 0;
    return answer;
}
