#ifndef _ALLOC_STAT_H_
#define _ALLOC_STAT_H_

#include "stddef.h"

typedef enum {
    STAT_TOTAL_ALLOC    = 0x01,
    STAT_TOTAL_FREE     = 0x02,
    STAT_IN_USE         = 0x04,
    STAT_LAST_ALLOC     = 0x08
} stat_type_t;

#define DEFAULT_STAT_FLAGS  (STAT_TOTAL_ALLOC | STAT_TOTAL_FREE | STAT_IN_USE)
#define DETAILED_STAT_FLAGS  (STAT_TOTAL_ALLOC | STAT_TOTAL_FREE | STAT_IN_USE | STAT_LAST_ALLOC)

void* stat_malloc(unsigned int module_id, unsigned int line, const char* function, size_t size);
void* stat_calloc(unsigned int module_id, unsigned int line, const char* function, size_t n, size_t size);
void stat_free(unsigned int module_id, unsigned int line, const char* function, void* ptr);
void stat_print(unsigned int module_id);
void alloc_stats(const stat_type_t flags);

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
    size_t total_free_size;
    alloc_entry_t* alloc_list;
} alloc_stat_t;

#endif /* _ALLOC_STAT_H_ */