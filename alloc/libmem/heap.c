#ifndef _HEAP_H_
#define _HEAP_H_

#include "libmem_api.h"
#include "libmem_defines.h"

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


uint32_t heap[HEADER_SIZE + HEAP_SIZE + HEADER_SIZE] = {
    [0] = (HEAP_SIZE & SIZE_MASK) & FREE_BIT,    /* Starting header */
    [1] = ((MODULE_ID_NONE & 0xFF) << 24) | FIRST_MAGIC, /* Control block */

    [HEADER_SIZE + HEAP_SIZE] = SECOND_MAGIC, /* Control block */
    [(HEADER_SIZE + HEAP_SIZE) + 1] = (HEAP_SIZE & SIZE_MASK) & FREE_BIT,  /* Ending header */
};

uint8_t* const heap_ptr = (uint8_t*)heap;

void *mem_start() {

    return heap_ptr;
}

void *mem_end() {

    return (heap_ptr + HEADER_SIZE_BYTES + HEAP_SIZE_BYTES + HEADER_SIZE_BYTES);
}

#endif /* _HEAP_H_ */