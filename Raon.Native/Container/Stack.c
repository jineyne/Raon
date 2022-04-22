#include "Stack.h"

void* stack_grow(void* stack, size_t element_size) {
    size_t new_capacity = (1 + 2 * STACK_CAPACITY(stack));
    size_t new_size = (new_capacity * element_size) + sizeof(FStackHeader);
    FStackHeader* new_header = NULL;
    if (stack == NULL) {
        new_header = (FStackHeader*)malloc(new_size);
        new_header->size = 0;
    }

    else {
        new_header = (FStackHeader*)realloc(STACK_HEADER(stack), new_size);
    }

    new_header->capacity = new_capacity;
    return ((char*)new_header + sizeof(FStackHeader));
}