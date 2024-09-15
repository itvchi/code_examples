#ifndef _HEAP_H_
#define _HEAP_H_

#include "heap_api.h"
#include <stdint.h>
#include <stdbool.h>

/*
 *  +---------------+----------+-----------------------------------------------------------+
 *  | Offset        | Size     |                        Description                        |
 *  +---------------+----------+-----------------------------------------------------------+
 *  | 0x00          | 0x04     |  Starting header                                          |
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
 *  | 0x0C + x*0x04 | 0x0C     |  Ending header                                            |
 *  |               |          |   - [31:3]     : block size (8 bytes aligned)             |
 *  |               |          |   - [0]        : is_allocated                             |
 *  +---------------+----------+-----------------------------------------------------------+
 */

#define HEADER_SIZE         2
#define HEADER_SIZE_BYTES   2 * sizeof(uint32_t)
#define SIZE_MASK           0xFFFFFFF8
#define SIZE_WORD           0

#define FREE_BIT            ~0x00000001
#define ALLOC_BIT           0x00000001

#define MODULE_ID_NONE      0x00
#define FIRST_MAGIC         0x00AD2024
#define SECOND_MAGIC        0xDEADBEEF
#define CB_SIZE             1
#define CB_SIZE_BYTES       sizeof(uint32_t)             


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


bool in_heap_range(void *ptr) {
    
    return ((uint8_t*)ptr < (heap_ptr + sizeof(uint32_t) * HEAP_SIZE));
}

bool is_free(void *ptr) {

    return !((*(uint32_t*)ptr) & ALLOC_BIT);
}

size_t size_in_header(void *ptr) {

    return (((uint32_t*)ptr)[SIZE_WORD] & SIZE_MASK);
}

bool is_big_enough(void *ptr, const size_t size) {

    return (size_in_header(ptr) >= size);
}

void set_new_size(void *ptr, const size_t size) {

    *(uint32_t*)ptr = size;
    *(uint32_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + size + CB_SIZE_BYTES) = size;
}

void mark_alloc(void *ptr, const size_t size) {

    *(uint32_t*)ptr |= ALLOC_BIT;
    *(uint32_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + size + CB_SIZE_BYTES) |= ALLOC_BIT;
}

void mark_free(void *ptr) {

    uint32_t *starting_header = (uint32_t*)((uint8_t*)ptr - HEADER_SIZE_BYTES);
    size_t size;

    *starting_header &= FREE_BIT;
    size = *starting_header;
    *(uint32_t*)((uint8_t*)ptr + size + CB_SIZE_BYTES) &= FREE_BIT;
}

void concat_right(void *ptr) {

    uint32_t *starting_header = (uint32_t*)((uint8_t*)ptr - HEADER_SIZE_BYTES);
    size_t size = *starting_header;
    uint32_t *next_starting_header = (uint32_t*)((uint8_t*)starting_header + HEADER_SIZE_BYTES + size + HEADER_SIZE_BYTES);
    uint32_t *next_ending_header;// = (uint32_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + old_size);
    size_t next_size;

    if (in_heap_range(next_starting_header) && is_free(next_starting_header)) {
        next_size = *next_starting_header;
        next_ending_header = (uint32_t*)((uint8_t*)next_starting_header + HEADER_SIZE_BYTES + next_size + CB_SIZE_BYTES);
        size = size + 2 * HEADER_SIZE_BYTES + next_size;
        
        *starting_header = size;
        *next_ending_header = size;
    }
}

void concat_left(void *ptr) {

    uint32_t *starting_header = (uint32_t*)((uint8_t*)ptr - HEADER_SIZE_BYTES);
    size_t size = *starting_header;
    uint32_t *ending_header = (uint32_t*)((uint8_t*)starting_header + HEADER_SIZE_BYTES + size);
    size_t prev_size;
    uint32_t *prev_ending_header = starting_header - HEADER_SIZE;
    uint32_t *prev_starting_header;

    if (((uint8_t*)prev_ending_header > heap_ptr) && is_free(prev_ending_header + 1)) {
        prev_size = *(prev_ending_header + 1);
        prev_starting_header = (uint32_t*)((uint8_t*)prev_ending_header - prev_size - HEADER_SIZE_BYTES);
        size = prev_size + 2 * HEADER_SIZE_BYTES + size;

        *prev_starting_header = size;
        *(ending_header + 1) = size;
    }
}

void edit_headers(void *ptr, const size_t old_size, const size_t size) {

    uint32_t *next_starting_header = (uint32_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + size + HEADER_SIZE_BYTES);
    uint32_t *next_ending_header = (uint32_t*)((uint8_t*)ptr + HEADER_SIZE_BYTES + old_size);
    //uint32_t *new_ending_header = next_starting_header - HEADER_SIZE_BYTES;
    size_t next_size = (uint8_t*)next_ending_header - ((uint8_t*)next_starting_header + HEADER_SIZE_BYTES);

    next_starting_header[SIZE_WORD] = next_size & SIZE_MASK; /* Still free */
    *(next_ending_header + CB_SIZE) = next_size & SIZE_MASK; /* Still free */
}

void *mem_alloc(size_t size) {

    uint8_t *alloc_ptr = NULL;
    uint8_t *starting_header = heap_ptr;

    size = ROUND_UP_TO_8_BYTES(size);

    /* Find first free block */
    while (in_heap_range(starting_header) && (!is_free(starting_header) || !is_big_enough(starting_header, size))) {
        starting_header = starting_header + size_in_header(starting_header) + HEADER_SIZE_BYTES;
    }

    if (in_heap_range(starting_header)) {
        size_t old_size = size_in_header(starting_header);
        if (old_size > size) {
            edit_headers(starting_header, old_size, size);
            set_new_size(starting_header, size);
            mark_alloc(starting_header, size);
            alloc_ptr = starting_header + HEADER_SIZE_BYTES;
        } else if (old_size == size) {
            set_new_size(starting_header, size);
            mark_alloc(starting_header, size);
            alloc_ptr = starting_header + HEADER_SIZE_BYTES;
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