#ifndef _ALLOC_STAT_H_
#define _ALLOC_STAT_H_

#include "stddef.h"

void* stat_malloc(const char* module, unsigned int line, const char* function, size_t size);
void* stat_calloc(const char* module, unsigned int line, const char* function, size_t n, size_t size);
void stat_free(const char* module, unsigned int line, const char* function, void* ptr);

#endif /* _ALLOC_STAT_H_ */