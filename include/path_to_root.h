#ifndef PATH_TO_ROOT_H
#define PATH_TO_ROOT_H

#include <stdbool.h>
#include <stdio.h>

#include "trie.h"
#include "io.h"

void flush_path_buffer(FILE *stream);

void write_path_to_root_reversed(node_t *node);

int get_first_element(node_t *node);

#endif //PATH_TO_ROOT_H
