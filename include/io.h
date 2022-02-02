#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdbool.h>

#include "constants.h"

void write_to_file(int buff, int wordSizeBits, FILE *stream);

void end_writing(int wordSizeBits, FILE *stream);

int read_single_word(int countBit, FILE *stream);

#endif //IO_H
