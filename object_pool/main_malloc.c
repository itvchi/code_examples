#include <stdlib.h>
#include "object.h"

size_t test_elements = TEST_ELEMENTS_NUM;
size_t max_per_loop = MAX_PER_LOOP;

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
            objs[idx] = malloc(sizeof(object_t));
        }
        for (idx = 0; idx < elements_in_round; idx++) {
            free(objs[idx]);
        }
    }

    return 0;
}
