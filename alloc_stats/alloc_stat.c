#include "alloc_stat.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>
#include <string.h>

static timestamp_t get_timestamp() {

    timestamp_t                             ts;
    struct timeval                          tv;

    gettimeofday(&tv,NULL);
    ts.sec = tv.tv_sec;
    ts.usec = tv.tv_usec;

    return ts;
}

static alloc_stat_t module_info[100];

static void stat_last_alloc(alloc_stat_entry_t *last_alloc, unsigned int line, const char* function, size_t size) {

    last_alloc->timestamp = get_timestamp();
    last_alloc->size = size;
    last_alloc->line = line;
    last_alloc->function = function;
}

void* stat_malloc(unsigned int module_id, unsigned int line, const char* function, size_t size) {

    assert(module_id < 100);
    
    stat_last_alloc(&(module_info[module_id].last_alloc), line, function, size);
    module_info[module_id].total_alloc_size += size;
    
    return malloc(size);
}

void* stat_calloc(unsigned int module_id, unsigned int line, const char* function, size_t n, size_t size) {

    assert(module_id < 100);
    
    stat_last_alloc(&(module_info[module_id].last_alloc), line, function, size);
    module_info[module_id].total_alloc_size += (n * size);

    return calloc(n, size);
}

void stat_free(unsigned int module_id, unsigned int line, const char* function, void* ptr) {
    
    free(ptr);
}

static char* print_timestamp(char *buffer, const timestamp_t timestamp) {

    time_t                                  date_time;

    if (buffer) {
        date_time = timestamp.sec;
        strftime(buffer, 80, "%Y-%m-%d-%H:%M:%S", localtime(&date_time));
        size_t last = strlen(buffer);
        sprintf(&buffer[last], ".%06ldus", timestamp.usec);
    }

    return buffer;
}

void stat_print(unsigned int module_id) {

    char buffer[80];
    alloc_stat_entry_t *last_alloc = &module_info[module_id].last_alloc;
    printf("Last alloc - size: %ld, from: %s @%d, at: %s\n", last_alloc->size, last_alloc->function, last_alloc->line, print_timestamp(buffer, last_alloc->timestamp));
    printf("Total alloc size: %ld\n", module_info[module_id].total_alloc_size);
}