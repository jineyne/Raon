#ifndef __KEYWORD_H__
#define __KEYWORD_H__

#include "Token.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u16 *name;

    ETokenType type;
    UTokenValue value;
} FKeyword;

#ifdef __cplusplus
}
#endif

#endif // __KEYWORD_H__
