#include "libmem_api.h"
#include "common.h"

extern uint8_t *heap_ptr;

static bool is_big_enough(void *ptr, const size_t size);
static void set_new_size(void *ptr, const size_t size);
static void mark_alloc(void *ptr, const size_t size);
static void edit_headers(void *ptr, const size_t old_size, const size_t size);

void *mem_alloc(size_t size) {

    void *alloc_ptr = NULL;
    starting_header_t *starting_header = (starting_header_t*)heap_ptr;

    size = ROUND_UP_TO_8_BYTES(size);

    /* Find first free block */
    while (in_heap_range(starting_header) && (!is_free(starting_header) || !is_big_enough(starting_header, size))) {
        starting_header = get_next(starting_header);
    }

    if (in_heap_range(starting_header)) {
        size_t old_size = (((starting_header_t*)starting_header)->size_and_alloc & SIZE_MASK);
        if (old_size > size) {
            edit_headers(starting_header, old_size, size);
            set_new_size(starting_header, size);
            mark_alloc(starting_header, size);
            alloc_ptr = (uint8_t *)starting_header + HEADER_SIZE_BYTES;
        } else if (old_size == size) {
            set_new_size(starting_header, size);
            mark_alloc(starting_header, size);
            alloc_ptr = (uint8_t *)starting_header + HEADER_SIZE_BYTES;
        } else {
            /* An error ocurred */
        }
    } else {
        /* Not enough space on the heap */
    }

    return alloc_ptr;
}

/* Private functions */
static bool is_big_enough(void *ptr, const size_t size) {

    return ((((starting_header_t*)ptr)->size_and_alloc & SIZE_MASK) >= size);
}

static void set_new_size(void *ptr, const size_t size) {

    ((starting_header_t*)ptr)->size_and_alloc = size;
    ((ending_header_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + size))->size_and_alloc = size;
}

static void mark_alloc(void *ptr, const size_t size) {

    ((starting_header_t*)ptr)->size_and_alloc |= ALLOC_BIT;
    ((ending_header_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + size))->size_and_alloc |= ALLOC_BIT;
}

static void edit_headers(void *ptr, const size_t old_size, const size_t size) {

    starting_header_t *next_starting_header = (starting_header_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + size + HEADER_SIZE_BYTES);
    ending_header_t *next_ending_header = (ending_header_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + old_size);
    size_t next_size = (uint8_t*)next_ending_header - ((uint8_t*)next_starting_header + HEADER_SIZE_BYTES);

    next_starting_header->size_and_alloc = next_size & SIZE_MASK; /* Still free */
    next_ending_header->size_and_alloc = next_size & SIZE_MASK; /* Still free */
}