#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include "Prerequisites/PrerequisitesUtil.h"

#include "BaseSymbol.h"
#include "TypeSymbol.h"
#include "VarSymbol.h"

#ifdef __cplusplus
extern "C" {
#endif

DLL_EXPORT void FreeSymbol(FSymbol *symbol);

#ifdef __cplusplus
}
#endif

#endif // __SYMBOL_H__
