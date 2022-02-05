#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <stdbool.h>

#include "constants.h"

void write_to_file(int buff, int wordSizeBits, FILE *stream);

void flush_writing_buffer(FILE *stream);

#endif //OUTPUT_H
