#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdbool.h>

#include "constants.h"

void write_to_file(int buff, int wordSizeBits, FILE *stream);

int read_single_word(int countBit, FILE *stream);

void flush_writing_buffer(FILE *stream);

#endif //IO_H
