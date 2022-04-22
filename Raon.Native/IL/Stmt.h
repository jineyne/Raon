#ifndef __STMT_H__
#define __STMT_H__

#include "CoreMinimal.h"
#include "ILBase.h"
#include "ILType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_ILSTMT_MEMBERS DEFAULT_IL_MEMBERS

typedef struct {
    DEFAULT_ILSTMT_MEMBERS
} FStmt;

#ifdef __cplusplus
}
#endif

#endif // __STMT_H__
