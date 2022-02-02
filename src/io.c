#include <assert.h>
#include "io.h"

static int cntWriting = 0;

inline static void write_single_bit(bool bit, FILE *stream) {
    static char buffer = 0;
    if (bit) {
        buffer |= (1 << cntWriting);
    }
    cntWriting++;
    if (cntWriting == 8) {
        fputc(buffer, stream);
        buffer = cntWriting = 0;
    }
}

void write_to_file(int buff, int wordSizeBits, FILE *stream) {
    //can be optimized, by writing ((size / 8) * 8) with a single fwrite
    for (int i = 0; i < wordSizeBits; ++i) {
        write_single_bit((buff >> i) & 1, stream);
    }
}

void flushWritingBuffer(FILE *stream) {
    while (cntWriting != 0) {
        write_single_bit(0, stream);
    }
}

static char readingBuffer = 0;
static int readingCnt = 8;

static inline int read_single_bit(FILE *stream) {
    if (readingCnt == 8) {
        if (feof(stream)) {
            return EOF;
        }
        readingBuffer = getc(stream);
        if (readingBuffer == EOF) {
            return EOF;
        }
        readingCnt = 0;
    }
    return (readingBuffer >> (readingCnt++)) & 1;
}

int read_single_word(int countBit, FILE *stream) {
    if (readingCnt == 8 && feof(stream)) {
        return EOF;
    }
    int res = 0;
    for (int i = 0; i < countBit; ++i) {
        int curr_bit = read_single_bit(stream);
        if (curr_bit == EOF) {
            return EOF;
        }
        res |= (curr_bit << i);
    }
    return res;
}
//abc
//def

//cbafed