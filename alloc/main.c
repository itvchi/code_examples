#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "libmem/libmem_api.h"

typedef struct {
    char c;
    int i;
    short s;
} custom_t;

int main(int argc, char const *argv[]) {

    printf("Heap starts @%p\n", mem_start());
    printf("Heap ends @%p\n", mem_end());
    printf("\n");

    /* mem_alloc() test */
    int *new_int = mem_alloc(sizeof(int));
    printf("Alloc int @%p\n", new_int);

    double *new_double = mem_alloc(sizeof(double));
    printf("Alloc double @%p\n", new_double);

    custom_t *new_custom = mem_alloc(sizeof(custom_t));
    printf("Alloc custom_t @%p\n", new_custom);

    char *new_char = mem_alloc(sizeof(char));
    printf("Alloc char @%p\n", new_char);

    float *new_float = mem_alloc(sizeof(float));
    printf("Alloc float @%p\n", new_float);

    int *int_array = mem_alloc(16 * sizeof(int));
    printf("Alloc int_array @%p\n", int_array);

    char *char_array = mem_alloc(32 * sizeof(char));
    printf("Alloc char_array @%p\n", char_array);
    printf("\n");


    /* mem_free() test */
    mem_free(new_double);
    mem_free(new_int);
    mem_free(new_char);
    mem_free(int_array);
    mem_free(new_float);

    /* Should alloc same as before */
    new_double = mem_alloc(sizeof(new_double));
    printf("Alloc double @%p\n", new_double);

    new_int = mem_alloc(sizeof(int));
    printf("Alloc int @%p\n", new_int);

    int_array = mem_alloc(16 * sizeof(int));
    printf("Alloc int_array @%p\n", int_array);

    int_array = mem_alloc(64 * sizeof(int));
    printf("Alloc int_array @%p\n", int_array);

    char_array = mem_alloc(32 * sizeof(char));
    printf("Alloc char_array @%p\n", char_array);

    return 0;
}
