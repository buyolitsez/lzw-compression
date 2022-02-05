#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "encode.h"
#include "decode.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "should be exactly three arguments\n");
        return 0;
    }
    char *fromFile, *toFile;
    fromFile = argv[2];
    toFile = argv[3];
    if (strcmp("encode", argv[1]) == 0)
        encode_to_file(fromFile, toFile);
    else if (strcmp("decode", argv[1]) == 0)
        decode_to_file(fromFile, toFile);
    else
        fprintf(stderr, "%s\n", "unknown command");

    if (errno) {
        fprintf(stderr, "%s\n", strerror(errno));
        return errno;
    }
    return 0;
}
