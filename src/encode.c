#include "encode.h"


void encode_to_file(char *fromFile, char *toFile) {
    FILE *inputFile = fopen(fromFile, "rb");
    FILE *outputFile = fopen(toFile, "wb");
    if (inputFile == NULL || outputFile == NULL) {
        return;
    }
    node_t *root = init();
    int currWord = read_single_word(ALPHABET_SIZE_BITS, inputFile);
    while (currWord != EOF) {
        node_t *currNode = root;
        while (currWord != EOF && currNode->child[currWord] != NULL) {
            currNode = currNode->child[currWord];
            currWord = read_single_word(ALPHABET_SIZE_BITS, inputFile);
        }
        fprintf(stderr, "%d ", currNode->index);
        fprintf(stderr, " - %d \n", get_word_size_bits());
        write_to_file(currNode->index, get_word_size_bits(), outputFile);
        if (currWord != EOF) {
            node_t *res;
            create_node(&root, currNode, currWord, &res);
            res;
        }
    }
    write_to_file(EOI, get_word_size_bits(), outputFile);
    flush_writing_buffer(outputFile);
    fclose(inputFile);
    fclose(outputFile);
    delete_trie(root);
}
