#include <stdio.h>
#include "trie.h"

#define CLC 256
#define EOI 257

int main() {
    node_t *root = init();
    char str[100], c;
    int id = 0;
    while ((c = getchar()) != '\n') {
        str[id++] = c;
    }
    str[id] = '\0';
    printf("%s\n", str);
    for (int i = 0; i < id; ++i) {
        str[i] = str[i] - 'A' + 1;
    }
    for (int i = 0; i < id;) {
        int j = i;
        node_t *curr_node = root;
        while (j < id && curr_node->child[str[j]] != NULL) {
            curr_node = curr_node->child[str[j]];
            ++j;
        }
        printf("%d ", curr_node->index);
        if (j != id) {
            curr_node->child[str[j]] = create_node();
        }
        i = j;
    }
    return 0;
}
// abdabccabcdab
// 0 1 3 4 2 2 7 6 1

//TOBEORNOTTOBEORTOBEORNOT
//20 15 2 5 15 18 14 15 20 27 29 31 36 30 32 34
