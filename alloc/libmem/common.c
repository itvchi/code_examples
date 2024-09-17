#include "common.h"
#include <stdint.h>

extern uint8_t *heap_ptr;

starting_header_t *get_starting(void *ptr) {

    return (starting_header_t*)((uint8_t*)ptr - HEADER_SIZE_BYTES);
} 

starting_header_t *get_next(starting_header_t *this) {

    return (starting_header_t*)((uint8_t*)this + HEADER_SIZE_BYTES + (this->size_and_alloc & SIZE_MASK) + HEADER_SIZE_BYTES);
}

ending_header_t *get_ending(starting_header_t *this) {

    return (ending_header_t*)((uint8_t*)this + HEADER_SIZE_BYTES + (this->size_and_alloc & SIZE_MASK));
}

bool is_free(void *ptr) {

    return !((*(uint32_t*)ptr) & ALLOC_BIT);
}

bool in_heap_range(void *ptr) {
    
    return ((uint8_t*)ptr < (heap_ptr + sizeof(uint32_t) * HEAP_SIZE));
}