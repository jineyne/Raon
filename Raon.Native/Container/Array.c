#include "Array.h"

void *array_grow(void *arr, size_t element_size) {
    size_t new_capacity = (1 + 2 * ARRAY_CAPACITY(arr));
    size_t new_size = (new_capacity * element_size) + sizeof(FArrayHeader);
    FArrayHeader *new_header = NULL;
    if (arr == NULL) {
        new_header = (FArrayHeader*)malloc(new_size);
        new_header->size = 0;
    } else {
        new_header = (FArrayHeader*)realloc(ARRAY_HEADER(arr), new_size);
    }

    new_header->capacity = new_capacity;
    return ((char*)new_header + sizeof(FArrayHeader));
}

void *array_resize(void *arr, size_t new_capacity, size_t element_size) {
    size_t new_size = (new_capacity * element_size) + sizeof(FArrayHeader);
    FArrayHeader *new_header = NULL;
    if (arr == NULL) {
        new_header = (FArrayHeader*)malloc(new_size);
    } else {
        new_header = (FArrayHeader*)realloc(ARRAY_HEADER(arr), new_size);
    }

    new_header->size = new_capacity;
    new_header->capacity = new_capacity;
    return ((char*)new_header + sizeof(FArrayHeader));
}
