#define MODULE_ID   1
#define MODULE_NAME "main"
#include "alloc_stat_api.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {

    int* ptr;
    ptr = (int*)MALLOC(100);
    stat_print(MODULE_ID);
    ptr = (int*)MALLOC(150);
    stat_print(MODULE_ID);
    FREE(ptr);
    stat_print(MODULE_ID);
    ptr = (int*)MALLOC(150);
    stat_print(MODULE_ID);
    ptr = (int*)MALLOC(100);
    stat_print(MODULE_ID);
    ptr = (int*)MALLOC(250);
    stat_print(MODULE_ID);

    if (ptr) {
        FREE(ptr);
    }

    return 0;
}
