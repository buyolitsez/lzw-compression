#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "constants.h"
#include "input.h"
#include "output.h"
#include "trie.h"
#include "path_to_root.h"

void decode_to_file(char *fromFile, char *toFile);

#endif //DECODE_H
