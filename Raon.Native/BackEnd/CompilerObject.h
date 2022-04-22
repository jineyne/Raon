#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "CoreMinimal.h"
#include "BackEnd/BackEndDefines.h"
#include "Value/Value.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    FValue *constants;
    int64_t *codes;
} FCompilerObject;

DLL_EXPORT FCompilerObject *CreateCompilerObject();
DLL_EXPORT void FreeCompilerObject(FCompilerObject *object);

DLL_EXPORT int64_t AppendDoubleConstant(FCompilerObject *object, double constant);
DLL_EXPORT int64_t AppendStringConstant(FCompilerObject *object, FString *constant);

DLL_EXPORT void SerializeObject(FCompilerObject *object, char **out);
DLL_EXPORT bool DeserializeObject(FCompilerObject *object, char *in);

#ifdef __cplusplus
}
#endif

#endif // __OBJECT_H__
