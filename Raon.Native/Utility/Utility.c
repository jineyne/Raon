#include "Utility.h"

#include "Error.h"
#include "Locale.h"

size_t CombineHash(size_t hash, size_t hash2) {
    return hash2 + 0x9e3779b9 + (hash << 6) + (hash >> 2);
}

static void print(u16 *msg) {
    wprintf(msg);
}

void InitRaon() {
    // TODO: Get locale from argument?
    SetLocale(LOCALE_KO);
    AddLogger(print);

    ClearError();
}
