#ifndef _LIB_DEFINES_H_
#define _LIB_DEFINES_H_

#include <stdint.h>

#define HEADER_SIZE_BYTES   2 * sizeof(uint32_t)
#define FREE_BIT            ~0x00000001
#define SIZE_MASK           0xFFFFFFF8
#define HEADER_SIZE         2
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


typedef struct {
    uint32_t size_and_alloc;
    uint32_t control_block;
} starting_header_t;

typedef struct {
    uint32_t control_block;
    uint32_t size_and_alloc;
} ending_header_t;

#endif