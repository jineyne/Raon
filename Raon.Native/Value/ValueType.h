#ifndef __VALUETYPE_H__
#define __VALUETYPE_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    VALUE_NONE,

    VALUE_BOOL,
    VALUE_INT,
    VALUE_REAL,
    VALUE_STRING,
} EValueType;

#ifdef __cplusplus
}
#endif

#endif // __VALUETYPE_H__
