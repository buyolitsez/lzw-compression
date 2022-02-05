#ifndef ENCODE_H
#define ENCODE_H

#include <errno.h>
#include <stdio.h>

#include "trie.h"
#include "input.h"
#include "output.h"

void encode_to_file(char *fromFile, char *toFile);

#endif // ENCODE_H
