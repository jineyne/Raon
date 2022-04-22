#ifndef __VALUE_H__
#define __VALUE_H__

#include "CoreMinimal.h"
#include "ValueType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_VALUE_MEMBERS EValueType type; int64_t data;

typedef struct {
    DEFAULT_VALUE_MEMBERS
} FValue;

#ifdef __cplusplus
}
#endif

#endif // __VALUE_H__