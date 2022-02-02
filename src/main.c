#include <stdio.h>
#include <errno.h>

#include "encode.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "should be exactly two arguments\n");
        return 0;
    }
    char *fromFile, *toFile;
    fromFile = argv[1];
    toFile = argv[2];
    encode_to_file(fromFile, toFile);
    if (errno) {
        fprintf(stderr, "%s", strerror(errno));
    }
    return 0;
}
