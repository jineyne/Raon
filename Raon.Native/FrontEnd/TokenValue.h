#ifndef __TOKENVALUE_H__
#define __TOKENVALUE_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef union TokenValue {
        int64_t integer;
        double real;
    } UTokenValue;

#ifdef __cplusplus
}
#endif

#endif //__TOKENVALUE_H__
