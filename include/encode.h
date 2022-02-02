#ifndef ENCODE_H
#define ENCODE_H

#include <errno.h>
#include <stdio.h>

#include "trie.h"
#include "io.h"

void encode_to_file(char *fromFile, char *toFile);

#endif // ENCODE_H
