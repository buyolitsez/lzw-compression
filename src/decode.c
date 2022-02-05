#include "decode.h"

void decode_to_file(char *fromFile, char *toFile) {
    FILE *inputFile = fopen(fromFile, "rb");
    FILE *outputFile = fopen(toFile, "wb");
    if (inputFile == NULL || outputFile == NULL) {
        return;
    }
    node_t *root = init();
    int currWord;
    node_t *prevNode = NULL;
    node_t *dict[(1 << MAX_WORD_SIZE_BITS)];
    memset(dict, 0, sizeof(dict));
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        dict[i] = root->child[i];
    }
    while (true) {
        if (prevNode == NULL) {
            currWord = read_single_word(get_word_size_bits(), inputFile);
            if (currWord == EOI) {
                break;
            }
            assert(dict[currWord] != NULL);
            prevNode = dict[currWord];
        } else {
            /* because in encoding, we firstly add element to dictionary and only then write next word,
            * but in decoding we firstly need to read next word and only then add element to dictionary,
            * so we increment index to calculate correct word size bits
            */
            if (increment_index(&root)) { // clear dictionary and start again
                prevNode = NULL;
                memset(dict, 0, sizeof(dict));
                for (int i = 0; i < ALPHABET_SIZE; ++i) {
                    dict[i] = root->child[i];
                }
                continue;
            }
            currWord = read_single_word(get_word_size_bits(), inputFile);
            decrement_index(); // because we increment it before
            if (currWord == EOI)
                break;
            if (dict[currWord] == NULL) { // word and element to be added are the same
                //prevWord + prevWord[0]
                assert(prevNode != NULL);
                int wordToParent = get_first_element(prevNode);
                dict[currWord] = create_node(&root, prevNode, wordToParent);
            } else {
                node_t *newNode = create_node(&root, prevNode, get_first_element(dict[currWord]));
                dict[newNode->index] = newNode;
            }
            prevNode = dict[currWord];
        }
        write_path_to_root_reversed(dict[currWord]);
        flush_path_buffer(outputFile);
    }
    flush_writing_buffer(outputFile);
    fclose(inputFile);
    fclose(outputFile);
    delete_trie(root);
}