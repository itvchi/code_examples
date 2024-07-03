#include "alloc_stat.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

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

static void append_entry(alloc_entry_t** alloc_list, void* alloc_ptr, size_t size) {

    alloc_entry_t*                          new_element = malloc(sizeof(alloc_entry_t));
    alloc_entry_t*                          entry = *alloc_list;

    new_element->alloc_ptr = alloc_ptr;
    new_element->alloc_size = size;
    new_element->next = NULL;

    if (entry) {
        /* Find last entry */
        while (entry && entry->next) {
            entry = entry->next;
        }
    
        entry->next = new_element;
    } else {
        *alloc_list = new_element;
    }
}

static bool delete_entry(alloc_entry_t** alloc_list, const void* alloc_ptr, size_t* size) {

    bool                                    found = false;
    alloc_entry_t*                          prev = NULL;
    alloc_entry_t*                          entry = *alloc_list;

    while (entry && (entry->alloc_ptr != alloc_ptr)) {
        prev = entry;
        entry = entry->next;
    }

    if (entry->alloc_ptr == alloc_ptr) {
        if (prev) {
            prev->next = entry->next;
        } 
        *size = entry->alloc_size;
        free(entry);
        found = true;
    }

    return found;
}

void* stat_malloc(unsigned int module_id, unsigned int line, const char* function, size_t size) {

    assert(module_id < 100);
    
    stat_last_alloc(&(module_info[module_id].last_alloc), line, function, size);
    module_info[module_id].total_alloc_size += size;

    void* alloc_ptr = malloc(size);

    if (alloc_ptr) {
        append_entry(&module_info[module_id].alloc_list, alloc_ptr, size);
    }
    
    return alloc_ptr;
}

void* stat_calloc(unsigned int module_id, unsigned int line, const char* function, size_t n, size_t size) {

    assert(module_id < 100);
    
    stat_last_alloc(&(module_info[module_id].last_alloc), line, function, size);
    module_info[module_id].total_alloc_size += (n * size);

    void* alloc_ptr = calloc(n, size);

    if (alloc_ptr) {
        append_entry(&module_info[module_id].alloc_list, alloc_ptr, n * size);
    }
    
    return alloc_ptr;
}

void stat_free(unsigned int module_id, unsigned int line, const char* function, void* ptr) {
    
    size_t size;

    if (delete_entry(&(module_info[module_id].alloc_list), ptr, &size)) {
        module_info[module_id].total_free_size += size;
    }

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

    char                                    buffer[80] = {0};
    alloc_stat_entry_t*                     last_alloc = &module_info[module_id].last_alloc;

    printf("Last alloc - size: %ld, from: %s @%d, at: %s\n", last_alloc->size, last_alloc->function, last_alloc->line, print_timestamp(buffer, last_alloc->timestamp));
    printf("Total alloc size: %ld\n", module_info[module_id].total_alloc_size);
}

void alloc_stats(const stat_type_t flags) {

    char                                    buffer[256] = {0};
    size_t                                  length_index = 0;

    printf("%15s  %15s  ", "Module id", "Module_name");
    length_index = sprintf(buffer, "%s", "_______________  _______________  ");

    if (flags & STAT_TOTAL_ALLOC) {
        printf("%15s  ", "Total alloc");
        length_index += sprintf(&buffer[length_index], "%s", "_______________  ");
    }

    if (flags & STAT_TOTAL_FREE) {
        printf("%15s  ", "Total free");
        length_index += sprintf(&buffer[length_index], "%s", "_______________  ");
    }

    if (flags & STAT_IN_USE) {
        printf("%15s  ", "In use");
        length_index += sprintf(&buffer[length_index], "%s", "_______________  ");
    }

    if (flags & STAT_LAST_ALLOC) {
        printf("%15s  ", "Last alloc");
        length_index += sprintf(&buffer[length_index], "%s", "__________________________________________________  ");
    }

    printf("\n");
    printf("%s\n", buffer);

    for (size_t module_id = 0; module_id < 100; module_id++) {
        
        size_t* alloc = &module_info[module_id].total_alloc_size;
        if (*alloc == 0) {
            continue;
        }

        printf("%15ld  %15s  ", module_id, "x");
        
        length_index = 0;
        size_t* free = &module_info[module_id].total_free_size;

        if (flags & STAT_TOTAL_ALLOC) {
            length_index += sprintf(&buffer[length_index], "%15ld  ", *alloc);
        }

        if (flags & STAT_TOTAL_FREE) {
            length_index += sprintf(&buffer[length_index], "%15ld  ", *free);
        }

        if (flags & STAT_IN_USE) {
            length_index += sprintf(&buffer[length_index], "%15ld  ", (*alloc - *free));
        }

        if (flags & STAT_LAST_ALLOC) {
            alloc_stat_entry_t* last_alloc = &module_info[module_id].last_alloc;
            length_index += sprintf(&buffer[length_index], "%ldB, f: %s() @%d at:",
                last_alloc->size, last_alloc->function, last_alloc->line);
            print_timestamp(&buffer[length_index], last_alloc->timestamp);
        }
        
        printf("%s\n", buffer);
    }

    printf("\n");
}