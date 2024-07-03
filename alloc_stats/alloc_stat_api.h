#ifndef _ALLOC_STAT_API_H_
#define _ALLOC_STAT_API_H_

#include "alloc_stat.h"

#if defined(MODULE_ID)

#if (MODULE_ID < 100)

#define MALLOC(size)        stat_malloc(MODULE_ID, __LINE__, __FUNCTION__, (size))
#define CALLOC(n, size)     stat_calloc(MODULE_ID, __LINE__, __FUNCTION__, (n), (size))    
#define FREE(ptr)           stat_free(MODULE_ID, __LINE__, __FUNCTION__, (ptr))

#else

#warning Macro MODULE_ID >= 100

#endif /* (MODULE_ID < 100) */

#else

#warning Macro MODULE_ID not defined - please define module name string before including alloc_stat.h file

#include "stddef.h"
#define MALLOC(size)        (NULL)
#define CALLOC(n, szie)     (NULL)
#define FREE(ptr)           ((void)0)

#endif /* defined(MODULE) */

#endif /* _ALLOC_STAT_API_H_ */