#include "encode.h"


void encode_to_file(char *fromFile, char *toFile) {
    FILE *inputFile = fopen(fromFile, "rb");
    FILE *outputFile = fopen(toFile, "wb");
    if (inputFile == NULL || outputFile == NULL) {
        return;
    }
    node_t *root = init();
    int currWord = read_single_word(SINGLE_READING_BITS, inputFile);
    int wordSizeBits = ALPHABET_SIZE_BITS + 1;
    while (currWord != EOF) {
        node_t *currNode = root;
        while (currWord != EOF && currNode->child[currWord] != NULL) {
            currNode = currNode->child[currWord];
            currWord = read_single_word(SINGLE_READING_BITS, inputFile);
        }
        fprintf(stderr, "%d ", currNode->index);
        write_to_file(currNode->index, wordSizeBits, outputFile);
        if (currWord != EOF) {
            create_node(currNode, currWord);
        }
    }
    write_to_file(EOI, wordSizeBits, outputFile);
    flushWritingBuffer(outputFile);
    fclose(inputFile);
    fclose(outputFile);
    delete_trie(root);
}
