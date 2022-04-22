#include "ILContext.h"

FILContext * CreateILContext() {
    FILContext *context = malloc(sizeof(FILContext));

    context->globalSymTab = CreateSymbolTable(CreateString(U16("GLOBAL")), NULL);
    context->localSymTab = CreateSymbolTable(CreateString(U16("LOCAL")), NULL);

    return context;
}

void FreeILContext(FILContext *context) {
    while (context->localSymTab != NULL) {
        FSymbolTable *parent = context->localSymTab->parent;
        FreeSymbolTable(context->localSymTab);
        context->localSymTab = parent;
    }

    FreeSymbolTable(context->globalSymTab);
}
