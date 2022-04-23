#ifndef __LOCATION_H__
#define __LOCATION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "CoreMinimal.h"
#include "FrontEnd/Token.h"

typedef struct {
    FString *source;
    FToken *token;
} FLocation;

DLL_EXPORT FLocation *CreateLocation(FString *source, FToken *token);
DLL_EXPORT void FreeLocation(FLocation *location);

#ifdef __cplusplus
}
#endif

#endif // __LOCATION_H__
