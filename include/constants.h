#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_WORD_SIZE_BITS 16 // should be not more than 31
#define ALPHABET_SIZE_BITS 8 // can be 1, 2, 4, 8

#define ALPHABET_SIZE (1 << ALPHABET_SIZE_BITS)
#define CLC (ALPHABET_SIZE) // reset dictionary
#define EOI (ALPHABET_SIZE + 1) // end of input

#define BUFFER_SIZE_WORDS 1024

#define CHAR_SIZE_BITS (sizeof(char) * 8)

#endif // CONSTANTS_H
