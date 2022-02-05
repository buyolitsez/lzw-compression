#include "input.h"

static int readingBuffer = 0;
static int readingCnt = CHAR_SIZE_BITS;

static inline int read_single_bit(FILE *stream) {
    //can be optimized by reading a big buffer with single read TODO
    if (readingCnt == CHAR_SIZE_BITS) {
        readingBuffer = getc(stream);
        if (readingBuffer == EOF)
            return EOF;
        readingCnt = 0;
    }
    return (readingBuffer >> (readingCnt++)) & 1;
}

int read_single_word(int countBit, FILE *stream) {
    if (readingCnt == CHAR_SIZE_BITS && feof(stream))
        return EOF;
    int res = 0;
    for (int i = 0; i < countBit; ++i) {
        int curr_bit = read_single_bit(stream);
        if (curr_bit == EOF)
            return EOF;
        res |= (curr_bit << i);
    }
    return res;
}
