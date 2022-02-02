#include "decode.h"

void decode_to_file(char *fromFile, char *toFile) {
    FILE *inputFile = fopen(fromFile, "rb");
    FILE *outputFile = fopen(toFile, "wb");
    if (inputFile == NULL || outputFile == NULL) {
        return;
    }
    node_t *root = init();
    int wordSizeBits = ALPHABET_SIZE_BITS + 1;
    int currWord;
    node_t *prevNode = NULL;
    node_t *dict[(1 << MAX_WORD_SIZE_BITS)];
    memset(dict, 0, sizeof(dict));
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        dict[i] = root->child[i];
    }
    while ((currWord = read_single_word(wordSizeBits, inputFile))
           != EOI) {
        bool isInDictionary = (dict[currWord] != NULL);
        if (!isInDictionary) {
            //prevWord + prevWord[0]
            assert(prevNode != NULL);
            int wordToParent = get_first_element(prevNode);
            dict[currWord] = create_node(prevNode, wordToParent);
        }
        write_path_to_root_reversed(dict[currWord]);
        flushPathBuffer(outputFile);
        // add new word to dict
        //prevWord +
        //dict[] = currIndex + 1;
        if (isInDictionary && prevNode != NULL) {
            node_t *newNode = create_node(prevNode, get_first_element(dict[currWord]));
            dict[newNode->index] = newNode;
        }
        prevNode = dict[currWord];
    }
    flushWritingBuffer(outputFile);
    fclose(inputFile);
    fclose(outputFile);
    delete_trie(root);
}