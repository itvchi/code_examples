#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap_api.h"

typedef struct {
    char c;
    int i;
    short s;
} custom_t;

int main(int argc, char const *argv[]) {

    void *heap = heap_start();
    printf("Heap starts @0x%p\n", heap);

    int *new_int = mem_alloc(sizeof(int));
    printf("Alloc int @0x%p\n", new_int);

    double *new_double = mem_alloc(sizeof(new_double));
    printf("Alloc double @0x%p\n", new_double);

    custom_t *new_custom = mem_alloc(sizeof(custom_t));
    printf("Alloc custom_t @0x%p\n", new_custom);

    int *new_char = mem_alloc(sizeof(char));
    printf("Alloc char @0x%p\n", new_char);

    double *new_float = mem_alloc(sizeof(new_float));
    printf("Alloc float @0x%p\n", new_float);

    return 0;
}
