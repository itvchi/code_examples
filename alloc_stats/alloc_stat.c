#include "alloc_stat.h"
#include <stdlib.h>
#include <stdio.h>

void* stat_malloc(const char* module, unsigned int line, const char* function, size_t size) {

    printf("Called malloc(%ld) from function: %s @ %d line\n", size, function, line);
    return malloc(size);
}

void* stat_calloc(const char* module, unsigned int line, const char* function, size_t n, size_t size) {

    printf("Called calloc(%ld, %ld) from function: %s @ %d line\n", n, size, function, line);
    return calloc(n, size);
}

void stat_free(const char* module, unsigned int line, const char* function, void* ptr) {
    
    printf("Called free(%p) from function: %s @ %d line\n", ptr, function, line);
    free(ptr);
}