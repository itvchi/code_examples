#ifndef _HEAP_API_H_
#define _HEAP_API_H_

#include <stddef.h>

#define HEAP_SIZE_BYTES 148

void *heap_start();
void *mem_alloc(const size_t size);

#endif /* _HEAP_API_H_ */