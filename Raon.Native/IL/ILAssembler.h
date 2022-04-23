#ifndef __ILASSEMBLER_H__
#define __ILASSEMBLER_H__

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
} FILAssembler;

DLL_EXPORT FILAssembler *CreateILAssembler();
DLL_EXPORT void FreeILAssembler(FILAssembler *assembler);

DLL_EXPORT FILBase *ILGenerate(FILAssembler *assembler, FBaseNode *node);

#ifdef __cplusplus
}
#endif

#endif // __ILASSEMBLER_H__
