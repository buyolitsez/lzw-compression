#include <assert.h>
#include "io.h"


inline static void write_single_bit(bool bit, FILE *stream) {
    static char buffer = 0;
    static int cnt = 0;

    buffer |= ((1 << cnt) & bit);
    cnt++;
    if (cnt == 8) {
        fwrite(&buffer, sizeof(char), 1, stream);
        cnt = buffer = 0;
    }
}

void write_to_file(int buff, int wordSizeBits, FILE *stream) {
    //can be optimized, by writing ((size / 8) * 8) with a single fwrite
    for (int i = 0; i < wordSizeBits; ++i) {
        write_single_bit((buff >> i) & 1, stream);
    }
}

inline void end_writing(int wordSizeBits, FILE *stream) {
    write_to_file(EOI, wordSizeBits, stream);
    write_to_file(0, 8, stream); // flush fwrite
}

static char readingBuffer = 0;
static int readingCnt = 8;

static inline bool read_single_bit(FILE *stream) {
    if (readingCnt == 8) {
        readingBuffer = getc(stream);
        readingCnt = 0;
    }
    return (readingBuffer >> (readingCnt++)) & 1;
}

int read_single_word(int countBit, FILE *stream) {
    if (readingCnt == 8 && feof(stream)) {
        return -1;
    }
    int res = 0;
    for (int i = 0; i < countBit; ++i) {
        int curr_bit = read_single_bit(stream);
        if (curr_bit == -1) {
            return -1;
        }
        res |= (curr_bit << i);
    }
    return res;
}
