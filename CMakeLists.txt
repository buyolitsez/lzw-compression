cmake_minimum_required(VERSION 3.21)
project(lzw_compression C)

set(CMAKE_C_STANDARD 23)

include_directories(include/)

add_executable(lzw_compression src/main.c include/trie.h src/trie.c include/constants.h include/encode.h include/io.h src/encode.c src/io.c)
