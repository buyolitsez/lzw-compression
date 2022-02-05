#include "output.h"

static int cntWriting = 0;

inline static void write_single_bit(bool bit, FILE *stream) {
    // optimize with a big buffer and single write the whole TODO
    static int buffer = 0;
    buffer |= (bit << cntWriting++);
    if (cntWriting == CHAR_SIZE_BITS) {
        fputc(buffer, stream);
        buffer = cntWriting = 0;
    }
}

void write_to_file(int buff, int wordSizeBits, FILE *stream) {
    for (int i = 0; i < wordSizeBits; ++i)
        write_single_bit((buff >> i) & 1, stream);
}

void flush_writing_buffer(FILE *stream) {
    while (cntWriting != 0)
        write_single_bit(0, stream);
}
