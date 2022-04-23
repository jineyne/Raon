#include "String.h"

FString *CreateString(const u16 *str) {
    FString *string = malloc(sizeof(FString));

    string->length = u16len(str);
    string->data = malloc(sizeof(u16) * (string->length + 1));
    string->data = u16ncpy(string->data, str, string->length);
    string->data[string->length] = '\0';


    return string;
}

FString *CopyString(const FString *str) {
    FString *string = malloc(sizeof(FString));

    string->length = str->length;
    string->data = malloc(sizeof(u16) * (string->length + 1));
    string->data = u16ncpy(string->data, str->data, string->length);
    string->data[string->length] = '\0';


    return string;
}

FString *CreateStringWithLength(const u16 *str, size_t len) {
    FString *string = malloc(sizeof(FString));

    string->length = len;
    string->data = malloc(sizeof(u16) * (string->length + 1));
    string->data = u16ncpy(string->data, str, string->length);
    string->data[string->length] = '\0';


    return string;
}

void FreeString(FString *this) {
    if (this == NULL) {
        return;
    }

    free(this->data);
    free(this);

    this = NULL;
}

size_t HashString(FString *string) {
    if (string == NULL) {
        return 0;
    }

    size_t hash = 0;

    for (int i = 0; i < string->length; i++) {
        hash = 65599 * hash + string->data[i];
    }

    return hash ^ (hash >> 16);
}
