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

    FValue *stacks;
    FValue *memory;

    bool running;

    size_t pc;
    FValue registers[16];

    FSymbolTable *global;
} FVM;

DLL_EXPORT FVM *CreateVM();
DLL_EXPORT void FreeVM(FVM *vm);

DLL_EXPORT void Execute(FVM *vm, FCompilerObject *object);

DLL_EXPORT void ExecuteSource(FVM *vm, u16 *str);

#ifdef __cplusplus
}
#endif

#endif // __VM_H__
