#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "CoreMinimal.h"

#include "IL/IL.h"

#include "BackEnd/CompilerObject.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Compiler {
    size_t index;
    char phase;

    FCompilerObject *object; // Current Object
} FCompiler;

DLL_EXPORT FCompiler *CreateCompiler();
DLL_EXPORT void FreeCompiler(FCompiler *compiler);

DLL_EXPORT FCompilerObject *CompileIL(FCompiler *compiler, FILBase *node);

#ifdef __cplusplus
}
#endif

#endif // __COMPILER_H__