#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <stdbool.h>
#include "object.h"

typedef struct {
    bool alloc;
    object_t obj;
} object_pool_t;

#endif /* _OBJECT_POOL_H_ */