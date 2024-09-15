#ifndef _HEAP_API_H_
#define _HEAP_API_H_

#include <stddef.h>

#define HEAP_SIZE_BYTES 256

void *heap_start();
void *heap_end();

void *mem_alloc(const size_t size);
void mem_free(void *ptr);

#endif /* _HEAP_API_H_ */