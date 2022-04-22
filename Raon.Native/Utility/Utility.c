#include "Utility.h"

size_t CombineHash(size_t hash, size_t hash2) {
    return hash2 + 0x9e3779b9 + (hash << 6) + (hash >> 2);
}
