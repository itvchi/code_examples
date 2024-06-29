#define MODULE  "main"
#include "alloc_stat_api.h"

int main(int argc, char const *argv[]) {

    int* ptr;
    ptr = (int*)MALLOC(100);

    if (ptr) {
        FREE(ptr);
    }

    return 0;
}
