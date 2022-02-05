#include "path_to_root.h"

static int bufferSize = 0;
static int *buffer = NULL;
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
        if (bufferSize == 0) {
            bufferSize = BUFFER_SIZE_WORDS;
            buffer = (int *) mymalloc(sizeof(int) * bufferSize);
        } else if (cnt == bufferSize) {
            int *newBuffer = (int *) mymalloc(sizeof(int) * 2ll * bufferSize);
            memcpy(newBuffer, buffer, sizeof(int) * bufferSize);
            free(buffer);
            buffer = newBuffer;
            bufferSize <<= 1;
        }
        buffer[cnt++] = currNode->wordToParent;
        currNode = currNode->parent;
    }
}

int get_first_element(node_t *node) {
    write_path_to_root_reversed(node);
    assert(cnt >= 0);
    int answer = buffer[cnt - 1];
    cnt = 0;
    return answer;
}
