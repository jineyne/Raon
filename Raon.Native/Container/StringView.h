#ifndef __STRINGVIEW_H__
#define __STRINGVIEW_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StringView {
    size_t length;
    u16 *data;
} FStringView;

DLL_EXPORT FStringView CreateStringView(u16 *data, size_t length);

DLL_EXPORT FStringView CreateStringViewFromCStr(u16 *data);

DLL_EXPORT FStringView TrimLeftStringView(FStringView view);
DLL_EXPORT FStringView TrimRightStringView(FStringView view);
DLL_EXPORT FStringView TrimStringView(FStringView view);

DLL_EXPORT bool IndexOfStringView(FStringView view, u16 c, size_t *index);

DLL_EXPORT FStringView ChopLeftStringView(FStringView *view, size_t size);
DLL_EXPORT FStringView ChopRightStringView(FStringView *view, size_t size);
DLL_EXPORT bool TryChopByDelimStringView(FStringView *view, u16 delim, FStringView *chunk);
DLL_EXPORT FStringView ChopByDelimStringView(FStringView *view, u16 delim);
DLL_EXPORT FStringView StringViewChopByStringView(FStringView *view, FStringView delim);

DLL_EXPORT bool StringViewStartWith(FStringView view, FStringView prefix);
DLL_EXPORT bool StringViewEndWith(FStringView view, FStringView suffix);

DLL_EXPORT int CompareStringView(FStringView lhs, FStringView rhs);


#ifdef __cplusplus
}
#endif

#endif // __STRINGVIEW_H__
