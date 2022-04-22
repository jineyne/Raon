#ifndef __ILASM_H__
#define __ILASM_H__

#include "CoreMinimal.h"
#include "ILContext.h"
#include "Stmt.h"
#include "AST/AST.h"
#include "FrontEnd/ColorGraph.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    FILContext *context;

    FSymbolTable *local; // TEST

    FStmt **statements;
    FColorGraph *graph;
    char phase;
} ILAssembler;

DLL_EXPORT ILAssembler *CreateILAssembler();
DLL_EXPORT void FreeILAssembler(ILAssembler *assembler);

DLL_EXPORT FILBase *ILGenerate(ILAssembler *assembler, FBaseNode *node);

#ifdef __cplusplus
}
#endif

#endif // __ILASM_H__
