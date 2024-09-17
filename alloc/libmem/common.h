#ifndef _COMMON_H_
#define _COMMON_H_

#include "libmem_defines.h"
#include <stdbool.h>

starting_header_t *get_starting(void *ptr);
starting_header_t *get_next(starting_header_t *this);
ending_header_t *get_ending(starting_header_t *this);
bool is_free(void *ptr);
bool in_heap_range(void *ptr);

#endif /* _COMMON_H_ */