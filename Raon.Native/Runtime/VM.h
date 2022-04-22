#ifndef __VM_H__
#define __VM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "CoreMinimal.h"
#include "BackEnd/CompilerObject.h"

typedef struct {
    FCompilerObject *object;

    FValue *stacks;
    FValue *memory;

    bool running;

    size_t pc;
    FValue registers[16];
} FVM;

DLL_EXPORT FVM *CreateVM();
DLL_EXPORT void FreeVM(FVM *vm);

DLL_EXPORT void Execute(FVM *vm, FCompilerObject *object);

#ifdef __cplusplus
}
#endif

#endif // __VM_H__
