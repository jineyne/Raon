#ifndef __VM_H__
#define __VM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "CoreMinimal.h"
#include "BackEnd/CompilerObject.h"
#include "Symbol/SymbolTable.h"

typedef struct {
    FCompilerObject *object;

    // TODO: realloc
    FValue stacks[64];
    FValue memory[64];

    bool running;

    size_t pc;

    FValue registers[REG_COUNT];

    FSymbolTable *global;
} FVM;

DLL_EXPORT FVM *CreateVM();
DLL_EXPORT void FreeVM(FVM *vm);

DLL_EXPORT void Execute(FVM *vm, FCompilerObject *object);

DLL_EXPORT void ExecuteSource(FVM *vm, u16 *str);

DLL_EXPORT bool TryGetBoolValueByName(FVM *vm, u16 *name, bool *out);
DLL_EXPORT bool TryGetIntegerValueByName(FVM *vm, u16 *name, int *out);
DLL_EXPORT bool TryGetRealValueByName(FVM *vm, u16 *name, double *out);
DLL_EXPORT bool TryGetStringValueByName(FVM *vm, u16 *name, u16 **out);

#ifdef __cplusplus
}
#endif

#endif // __VM_H__
