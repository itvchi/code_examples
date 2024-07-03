#define MODULE_ID   1
#define MODULE_NAME "main"
#include "alloc_stat_api.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {

    int* i_ptr;
    double* d_ptr;
    
    i_ptr = (int*)MALLOC(sizeof(int));
    i_ptr = (int*)CALLOC(2, sizeof(int));
    FREE(i_ptr);
    alloc_stats(DEFAULT_STAT_FLAGS); /* sizeof(int) should be leaked */
    
    i_ptr = (int*)MALLOC(10);
    d_ptr = (double*)MALLOC(sizeof(double));
    alloc_stats(DEFAULT_STAT_FLAGS);
    
    FREE(i_ptr);
    FREE(d_ptr);
    alloc_stats(DEFAULT_STAT_FLAGS);

    d_ptr = (double*)CALLOC(15, sizeof(double));
    i_ptr = (int*)MALLOC(20);
    alloc_stats(DETAILED_STAT_FLAGS);

    return 0;
}
