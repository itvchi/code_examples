#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "object_pool.h"

size_t test_elements = TEST_ELEMENTS_NUM;
size_t max_per_loop = MAX_PER_LOOP;

#define OBJECT_POOL_CAPACITY    MAX_PER_LOOP + 10
object_pool_t obj_pool[OBJECT_POOL_CAPACITY] = {0};

object_t *take() {

    static size_t last_taken = 0;
    size_t idx;
    object_t *obj = NULL;

    for (idx = last_taken; idx < OBJECT_POOL_CAPACITY; idx++) {
        if (obj_pool[idx].alloc == false) {
            obj_pool[idx].alloc = true;
            obj = &obj_pool[idx].obj;
            last_taken = idx;
            break;
        }
    }
    /* Traverse front of the pool if there is no free object found after last taken object */
    if (obj == NULL) {
        for (idx = 0; idx < last_taken; idx++) {
            if (obj_pool[idx].alloc == false) {
                obj_pool[idx].alloc = true;
                obj = &obj_pool[idx].obj;
                last_taken = idx;
                break;
            }
        }
    }

    // printf("Take object %ld (%p)\n", idx, obj);
    return obj;
}

void give(object_t *obj) {

    size_t idx = ((uintptr_t)obj - (uintptr_t)obj_pool) / sizeof(object_pool_t);
    assert(idx < OBJECT_POOL_CAPACITY);
    assert(obj_pool[idx].alloc);
    // printf("Give object %ld (%p)\n", idx, obj);
    obj_pool[idx].alloc = false;
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
