#ifndef __LOCALE_H__
#define __LOCALE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Prerequisites/PrerequisitesUtil.h"

typedef enum {
    LOCALE_KO = 0,
    LOCALE_EN,

    LOCALE_COUNT,
} ELocale;

DLL_EXPORT void SetLocale(ELocale locale);
DLL_EXPORT ELocale GetLocale();

#ifdef __cplusplus
}
#endif

#endif // __LOCALE_H__
