#ifndef _HEAP_H_
#define _HEAP_H_

#include "heap_api.h"
#include <stdint.h>
#include <stdbool.h>

/*
 *  +---------------+----------+-----------------------------------------------------------+
 *  | Offset        | Size     |                        Description                        |
 *  +---------------+----------+-----------------------------------------------------------+
 *  | 0x00          | 0x04     |  Size and alloc block                                     |
 *  |               |          |   - [31:3]     : block size (8 bytes aligned)             |
 *  |               |          |   - [0]        : is_allocated                             |
 *  +---------------+----------+-----------------------------------------------------------+
 *  | 0x04          | 0x04     |  Control block                                            |
 *  |               |          |   - [31:24]    : module_id                                |
 *  |               |          |   - [23:0]     : first_magic                              |
 *  +---------------+----------+-----------------------------------------------------------+
 *  | 0x08          | x * 0x04 |  Data                                                     |
 *  |               |          |  (padded to 8-byte align)                                 |
 *  +---------------+----------+-----------------------------------------------------------+
 *  | 0x08 + x*0x04 | 0x08     |  Control block                                            |
 *  |               |          |   - [31:0]     : second_magic                             |
 *  +---------------+----------+-----------------------------------------------------------+
 *  | 0x0C + x*0x04 | 0x0C     |  Size and alloc block                                     |
 *  |               |          |   - [31:3]     : block size (8 bytes aligned)             |
 *  |               |          |   - [0]        : is_allocated                             |
 *  +---------------+----------+-----------------------------------------------------------+
 */

typedef struct {
    uint32_t size_and_alloc;
    uint32_t control_block;
} starting_header_t;

typedef struct {
    uint32_t control_block;
    uint32_t size_and_alloc;
} ending_header_t;



#define HEADER_SIZE         2
#define HEADER_SIZE_BYTES   2 * sizeof(uint32_t)
#define SIZE_MASK           0xFFFFFFF8

#define FREE_BIT            ~0x00000001
#define ALLOC_BIT           0x00000001

#define MODULE_ID_NONE      0x00
#define FIRST_MAGIC         0x00AD2024
#define SECOND_MAGIC        0xDEADBEEF  

#define CB_SIZE_BYTES 4 /* to remove */   


#if !defined(HEAP_SIZE_BYTES)
    #error "HEAP_SIZE_BYTES was not defined properly"
#elif (HEAP_SIZE_BYTES & (HEAP_SIZE_BYTES - 1)) != 0
    #warning "HEAP_SIZE_BYTES is not a power of 2. Rounding up to the nearest power of 2."
#endif

#define ROUND_UP_TO_POWER_OF_2(x)   (1 << (32 - __builtin_clz((x) - 1)))
#define ROUND_UP_TO_8_BYTES(x)      (((x) + 7) & (-8))
#define HEAP_SIZE                   ROUND_UP_TO_POWER_OF_2(HEAP_SIZE_BYTES)
#define HEAP_ARRAY_SIZE             ((HEADER_SIZE + HEAP_SIZE + HEADER_SIZE) * sizeof(uint32_t))

uint32_t heap[HEADER_SIZE + HEAP_SIZE + HEADER_SIZE] = {
    [0] = (HEAP_SIZE & SIZE_MASK) & FREE_BIT,    /* Starting header */
    [1] = ((MODULE_ID_NONE & 0xFF) << 24) | FIRST_MAGIC, /* Control block */

    [HEADER_SIZE + HEAP_SIZE] = SECOND_MAGIC, /* Control block */
    [(HEADER_SIZE + HEAP_SIZE) + 1] = (HEAP_SIZE & SIZE_MASK) & FREE_BIT,  /* Ending header */
};

uint8_t* const heap_ptr = (uint8_t*)heap;

static starting_header_t *get_starting(void *ptr) {

    return (starting_header_t*)((uint8_t*)ptr - HEADER_SIZE_BYTES);
} 

static starting_header_t *get_next(starting_header_t *this) {

    return (starting_header_t*)((uint8_t*)this + HEADER_SIZE_BYTES + (this->size_and_alloc & SIZE_MASK) + HEADER_SIZE_BYTES);
}

static ending_header_t *get_ending(starting_header_t *this) {

    return (ending_header_t*)((uint8_t*)this + HEADER_SIZE_BYTES + (this->size_and_alloc & SIZE_MASK));
}

bool in_heap_range(void *ptr) {
    
    return ((uint8_t*)ptr < (heap_ptr + sizeof(uint32_t) * HEAP_SIZE));
}

/* To refactor */
bool is_free(void *ptr) {

    return !((*(uint32_t*)ptr) & ALLOC_BIT);
}

bool is_big_enough(void *ptr, const size_t size) {

    return ((((starting_header_t*)ptr)->size_and_alloc & SIZE_MASK) >= size);
}

void set_new_size(void *ptr, const size_t size) {

    ((starting_header_t*)ptr)->size_and_alloc = size;
    ((ending_header_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + size))->size_and_alloc = size;
}

void mark_alloc(void *ptr, const size_t size) {

    ((starting_header_t*)ptr)->size_and_alloc |= ALLOC_BIT;
    ((ending_header_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + size))->size_and_alloc |= ALLOC_BIT;
}

void mark_free(void *ptr) {

    starting_header_t *starting_header = get_starting(ptr);

    starting_header->size_and_alloc &= FREE_BIT;
    get_ending(starting_header)->size_and_alloc &= FREE_BIT;
}

void concat_right(void *ptr) {

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

void concat_left(void *ptr) {

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

void edit_headers(void *ptr, const size_t old_size, const size_t size) {

    starting_header_t *next_starting_header = (starting_header_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + size + HEADER_SIZE_BYTES);
    ending_header_t *next_ending_header = (ending_header_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + old_size);
    size_t next_size = (uint8_t*)next_ending_header - ((uint8_t*)next_starting_header + HEADER_SIZE_BYTES);

    next_starting_header->size_and_alloc = next_size & SIZE_MASK; /* Still free */
    next_ending_header->size_and_alloc = next_size & SIZE_MASK; /* Still free */
}

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

void *heap_start() {

    return heap_ptr;
}

void *heap_end() {

    return (heap_ptr + HEADER_SIZE_BYTES + HEAP_SIZE_BYTES + HEADER_SIZE_BYTES);
}

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

#endif /* _HEAP_H_ */