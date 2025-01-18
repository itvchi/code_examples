#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <stdbool.h>
#include "object.h"

typedef struct object_pool {
    bool alloc;
    object_t obj;
    struct object_pool *next;
} object_pool_t;

#endif /* _OBJECT_POOL_H_ */