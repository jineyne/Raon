#ifndef __STACK_H__
#define __STACK_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StackHeader {
    size_t size;
    size_t capacity;
} FStackHeader;

#define STACK_INIT(a, size)             ((a) ? (a = stack_grow(a, size)) : 0)
#define STACK_HEADER(a)                 ((FStackHeader *) ((char *)(a) - sizeof(FStackHeader)))
#define STACK_SIZE(a)                   ((a) ? STACK_HEADER(a)->size : 0)
#define STACK_CAPACITY(a)               ((a) ? STACK_HEADER(a)->capacity : 0)
#define STACK_FULL(a)                   (STACK_SIZE(a) == STACK_CAPACITY((a)))
#define STACK_PUSH(a, item)             ((STACK_FULL(a) ? (a = stack_grow(a, sizeof(*a))) : 0), (a[STACK_HEADER(a)->size++] = item))
#define STACK_PUSH_SAFE(a, item, type)  ((STACK_FULL(a) ? (a = (type *) stack_grow((void *) a, sizeof(*a))) : 0), (a[STACK_HEADER(a)->size++] = item))
#define STACK_FREE(a)                   ((a) ? (free(STACK_HEADER(a)), a = NULL) : 0)
#define STACK_CLEAR(a)                  ((a) ? (STACK_HEADER(a)->size = 0) : 0)
#define STACK_FOREACH(a, iter)          for(size_t __i = 0; __i < STACK_SIZE(a) && (iter = a[__i], 1); __i++)
#define STACK_POP(a)                    ((a) ? (STACK_HEADER(a)->size--, a + STACK_HEADER(a)->size) : 0)
#define STACK_PEEK(a)                   ((a) ? (a + STACK_HEADER(a)->size - 1) : 0)

DLL_EXPORT void* stack_grow(void* stack, size_t element_size);

#ifdef __cplusplus
}
#endif

#endif // __STACK_H__