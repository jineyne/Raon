#include "FStringBuffer.h"

#include "FStringBuffer.h"

FStringBuffer* CreateStringBuffer() {
    FStringBuffer* sb = malloc(sizeof(FStringBuffer));
    sb->size = 32;
    sb->length = 0;
    sb->data = malloc(sizeof(u16) * sb->size);

    return sb;
}

void FreeStringBuffer(FStringBuffer* sb) {
    free(sb->data);
    free(sb);
}

void AppendString(FStringBuffer *sb, FString *str) {
    while (sb->length + str->length >= sb->size) {
        sb->size += 32;
        sb->data = realloc(sb->data, sizeof(u16) * sb->size);
    }

    u16ncpy(sb->data + sb->length, str->data, str->length);
    sb->length += str->length;
}

void AppendCString(FStringBuffer* sb, u16* str) {
    size_t len = u16len(str);
    while (sb->length + len >= sb->size) {
        sb->size += 32;
        sb->data = realloc(sb->data, sizeof(u16) * sb->size);
    }

    u16ncpy(sb->data + sb->length, str, len);
    sb->length += len;
}

void AppendChar(FStringBuffer *sb, u16 ch) {
    size_t len = 1;
    while (sb->length + len >= sb->size) {
        sb->size += 32;
        sb->data = realloc(sb->data, sizeof(u16) * sb->size);
    }

    u16ncpy(sb->data + sb->length, &ch, 1);
    sb->length += len;
}

FString* StringBufferToString(FStringBuffer* sb) {
    return CreateStringWithLength(sb->data, sb->length);
}
