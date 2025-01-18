#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "object_pool.h"

size_t test_elements = TEST_ELEMENTS_NUM;
size_t max_per_loop = MAX_PER_LOOP;

#define OBJECT_POOL_CAPACITY    MAX_PER_LOOP + 10
object_pool_t obj_pool[OBJECT_POOL_CAPACITY] = {0};
object_pool_t *freelist = NULL;

__attribute__((constructor))
void object_pool_init() {

    size_t idx;

    for (idx = 0; idx < (OBJECT_POOL_CAPACITY - 1); idx++) {
        obj_pool[idx].next = &obj_pool[idx+1];
    }
    obj_pool[idx].next = NULL;
    freelist = &obj_pool[0];
}


object_t *take() {

    size_t idx;
    object_t *obj = NULL;

    if (freelist) {
        obj = &freelist->obj;
        freelist = freelist->next;
        idx = ((uintptr_t)obj - (uintptr_t)obj_pool) / sizeof(object_pool_t);
        // printf("Take object %d (%p)\n", idx, obj);
    }

    return obj;
}

void give(object_t *obj) {

    size_t idx = ((uintptr_t)obj - (uintptr_t)obj_pool) / sizeof(object_pool_t);

    assert(&obj_pool[idx].obj == obj);

    obj_pool[idx].next = freelist;
    freelist = &obj_pool[idx];
    // printf("Give object %ld (%p)\n", idx, obj);
}

int main(int argc, char const *argv[]) {

    size_t idx; 

    while (test_elements) {
        size_t elements_in_round = rand() % max_per_loop;
        if (elements_in_round > test_elements) {
            elements_in_round = test_elements;
        }
        test_elements -= elements_in_round;

        object_t *objs[elements_in_round];
        for (idx = 0; idx < elements_in_round; idx++) {
            objs[idx] = take();
        }
        for (idx = 0; idx < elements_in_round; idx++) {
            give(objs[idx]);
        }
    }

    return 0;
}
