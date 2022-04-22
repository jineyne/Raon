#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "CoreMinimal.h"
#include "Runtime/VM.h"

typedef struct {
    int argc; // arg count
    const u16 *op_str; // operation name
    bool (*func)(FVM *, uint16_t);
} FOp;

#ifdef __cplusplus
}
#endif

#endif // __INSTRUCTION_H__
