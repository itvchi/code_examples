#ifndef _ALLOC_STAT_H_
#define _ALLOC_STAT_H_

#include "stddef.h"

void* stat_malloc(unsigned int module_id, unsigned int line, const char* function, size_t size);
void* stat_calloc(unsigned int module_id, unsigned int line, const char* function, size_t n, size_t size);
void stat_free(unsigned int module_id, unsigned int line, const char* function, void* ptr);
void stat_print(unsigned int module_id);

typedef struct {
    long sec;
    long usec;
} timestamp_t;

typedef struct {
    timestamp_t timestamp;
    size_t size;
    const char* function;
    unsigned int line;
} alloc_stat_entry_t;


struct alloc_entry {
    void* alloc_ptr;
    size_t alloc_size;
    struct alloc_entry* next;
};

typedef struct alloc_entry alloc_entry_t;

typedef struct {
    alloc_stat_entry_t last_alloc;
    size_t total_alloc_size;
    alloc_entry_t* alloc_list;
} alloc_stat_t;

#endif /* _ALLOC_STAT_H_ */