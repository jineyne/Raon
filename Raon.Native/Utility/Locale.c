#include "Locale.h"

#include <locale.h>

#if COMPILER == COMPILER_MSVC
#include <windows.h>
#endif

static char *gLocaleStr[] = {
    "ko_KR.UTF-8",
    "en_US.UTF-8",
};

static ELocale gCurrentLocale = LOCALE_KO;

void SetLocale(ELocale locale) {
    gCurrentLocale = locale;

#if COMPILER == COMPILER_MSVC
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    setlocale(LC_ALL, gLocaleStr[gCurrentLocale]);
}

ELocale GetLocale() {
    return gCurrentLocale;
}
