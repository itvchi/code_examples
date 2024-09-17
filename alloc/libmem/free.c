#include "libmem_api.h"
#include "common.h"

extern uint8_t *heap_ptr;

static void mark_free(void *ptr);
static void concat_right(void *ptr);
static void concat_left(void *ptr);

void mem_free(void *ptr) {

    if (((uint8_t*)ptr >= (heap_ptr + HEADER_SIZE_BYTES)) && ((uint8_t*)ptr < (heap_ptr + sizeof(uint32_t) * HEAP_SIZE))) {
        mark_free(ptr);
        /* Firstly concat right, to not invalidate header of "ptr" frame */
        concat_right(ptr);
        concat_left(ptr);
    } else {
        /* Ptr over heap range */
    }
}

/* Private functions */
static void mark_free(void *ptr) {

    starting_header_t *starting_header = get_starting(ptr);

    starting_header->size_and_alloc &= FREE_BIT;
    get_ending(starting_header)->size_and_alloc &= FREE_BIT;
}

static void concat_right(void *ptr) {

    starting_header_t *starting_header = get_starting(ptr);
    starting_header_t *next_starting_header =  get_next(starting_header);
    ending_header_t *next_ending_header;
    size_t size = starting_header->size_and_alloc & SIZE_MASK;
    size_t next_size;

    if (in_heap_range(next_starting_header) && is_free(next_starting_header)) {
        next_size = next_starting_header->size_and_alloc & SIZE_MASK;
        next_ending_header = get_ending(next_starting_header);
        size = size + 2 * HEADER_SIZE_BYTES + next_size;
        
        starting_header->size_and_alloc = size;
        next_ending_header->size_and_alloc = size;
    }
}

static void concat_left(void *ptr) {

    starting_header_t *starting_header = get_starting(ptr);
    ending_header_t *ending_header = get_ending(starting_header);
    ending_header_t *prev_ending_header = (ending_header_t*)((uint8_t*)starting_header - HEADER_SIZE_BYTES);
    starting_header_t *prev_starting_header;
    size_t size = starting_header->size_and_alloc & SIZE_MASK;
    size_t prev_size;

    if (((uint8_t*)prev_ending_header > heap_ptr) && is_free(&prev_ending_header->size_and_alloc)) {
        prev_size = prev_ending_header->size_and_alloc;
        prev_starting_header = (starting_header_t*)((uint8_t*)prev_ending_header - prev_size - HEADER_SIZE_BYTES);
        size = prev_size + 2 * HEADER_SIZE_BYTES + size;

        prev_starting_header->size_and_alloc = size;
        ending_header->size_and_alloc = size;
    }
}