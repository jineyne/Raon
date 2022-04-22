#ifndef __REGEX_H__
#define __REGEX_H__

#include "CoreMinimal.h"
#include "String/UTF16.h"

// base on : https://github.com/kokke/tiny-regex-c

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct regex Regex;

    /**
     * Combile regex string pattern to regex array
     */
    DLL_EXPORT Regex* RegexCompile(const u16* pattern);

    /**
     * Find matches of the compiled pattern inside text
     */
    DLL_EXPORT int RegexMatch(Regex* pattern, const u16* text);

    /**
     * Find matches of the text pattern inside text
     * this function compile automatically first
     */
    DLL_EXPORT int RegexMatchPattern(const u16* pattern, const u16* text);

#ifdef __cplusplus
}
#endif

#endif // __REGEX_H__