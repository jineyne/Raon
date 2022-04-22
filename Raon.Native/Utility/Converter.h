#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "Prerequisites/PrerequisitesUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union Converter16 {
    size_t size;
    uint64_t uinteger;
    int64_t integer;
    double real;
    void *pointer;
    char bytes[16];
} FConverter16;

typedef union Converter8 {
    uint32_t uinteger;
    int32_t integer;
    float real;
    char bytes[8];
} FConverter8;

typedef union Converter4 {
    uint16_t uinteger;
    int16_t integer;
    char bytes[4];
} FConverter4;

#ifdef __cplusplus
}
#endif

#endif // __CONVERTER_H__