#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArrayHeader {
    size_t size;
    size_t capacity;
} FArrayHeader;

#define ARRAY_HEADER(a)                 ((FArrayHeader *) ((char *)(a) - sizeof(FArrayHeader)))
#define ARRAY_SIZE(a)                   ((a) ? ARRAY_HEADER(a)->size : 0)
#define ARRAY_CAPACITY(a)               ((a) ? ARRAY_HEADER(a)->capacity : 0)
#define ARRAY_FULL(a)                   (ARRAY_SIZE(a) == ARRAY_CAPACITY((a)))
#define ARRAY_PUSH(a, item)             ((ARRAY_FULL(a) ? (a = array_grow(a, sizeof(*a))) : 0), (a[ARRAY_HEADER(a)->size++] = item))
#define ARRAY_PUSH_SAFE(a, item, type)  ((ARRAY_FULL(a) ? (a = (type *) array_grow((void *) a, sizeof(*a))) : 0), (a[ARRAY_HEADER(a)->size++] = item))
#define ARRAY_FREE(a)                   ((a) ? (free(ARRAY_HEADER(a)), a = NULL) : 0)
#define ARRAY_CLEAR(a)                  ((a) ? (ARRAY_HEADER(a)->size = 0) : 0)
#define ARRAY_FOREACH(a, iter)          for(size_t __i = 0; __i < ARRAY_SIZE(a) && (iter = a[__i], 1); __i++)
#define ARRAY_RESIZE(a, new_size)       (a = array_resize(a, new_size, sizeof(*a)))

DLL_EXPORT void* array_grow(void* arr, size_t element_size);
DLL_EXPORT void* array_resize(void* arr, size_t new_capacity, size_t element_size);

#ifdef __cplusplus
}
#endif

#endif //__ARRAY_H__
