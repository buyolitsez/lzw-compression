#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_WORD_SIZE_BITS 16 // should be not more than 31
#define ALPHABET_SIZE_BITS 8

#define ALPHABET_SIZE (1 << ALPHABET_SIZE_BITS)
#define CLC (ALPHABET_SIZE) // reset dictionary
#define EOI (ALPHABET_SIZE + 1) // end of input

#define SINGLE_READING_BITS 8 // should be 1 or 2 or 4 or 8

#endif // CONSTANTS_H
