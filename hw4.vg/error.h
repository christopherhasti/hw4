// error.h
#ifndef ERROR_H
#define ERROR_H
#include <stdio.h>
#include <stdlib.h>

#define ERROR(msg, ...) do { \
    fprintf(stderr, "Error in %s at line %d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
} while(0)

#endif