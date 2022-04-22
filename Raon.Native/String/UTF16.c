#include "UTF16.h"

#include "Utility/Regex.h"

size_t u16len(const u16* str) {
    const u16* s = str;
    size_t length = 0;

    while ('\0' != *s) {
        int chsize = u16charsize(s);
        if (chsize == -1) {
            return -1;
        }
        else {
            s += chsize;
        }

        length++;
    }

    return length;
}

int u16cmp(const u16* str1, const u16* str2) {
    const u16* s1 = str1;
    const u16* s2 = str2;

    while (('\0' != *s1) || ('\0' != *s2)) {
        if (*s1 < *s2) {
            return -1;
        }
        else if (*s1 > *s2) {
            return 1;
        }

        s1++;
        s2++;
    }

    return 0;
}

void* u16cat(u16* dst, const u16* src) {
    u16* d = dst;
    const u16* s = src;

    while ('\0' != *d) {
        d++;
    }

    while ('\0' != *s) {
        *d++ = *s++;
    }

    *d = '\0';

    return dst;
}

void* u16ncat(u16* dst, const u16* src, size_t num) {
    u16* d = dst;
    const u16* s = src;

    while ('\0' != *d) {
        d++;
    }

    do {
        *d++ = *s++;
    } while (('\0' != *s) && (0 != --num));

    *d = '\0';

    return dst;
}

void* u16cpy(u16* dst, const u16* src) {
    u16* d = (u16*)dst;
    const u16* s = (const u16*)src;

    while ('\0' != *s) {
        *d++ = *s++;
    }

    *d = '\0';

    return dst;
}

void* u16ncpy(u16* dst, const u16* src, size_t num) {
    u16* d = (u16*)dst;
    const u16* s = (const u16*)src;
    size_t index;

    for (index = 0; index < num; index++) {
        d[index] = s[index];
        if ('\0' == s[index]) {
            break;
        }
    }

    // append null terminating byte
    for (; index < num; index++) {
        d[index] = 0;
    }

    return dst;
}

int u16charsize(const u16* peek) {
    if (*peek <= 0x10ffff) {
        return 1;
    }
    else if (*peek <= 0xfffffc00) {
        return 2;
    }
    else {
        return -1;
    }
}

int u16isspace(const u16 ch) {
    if ((ch >= 9 && ch <= 13) || ch == 32) {
        return true;
    }

    return false;
}

int u16isalpha(const u16 ch) {
    return ((ch >= 'a') && (ch <= 'z') || (ch >= 'A') && (ch <= 'Z'));
}

int u16isdigit(const u16 ch) {
    if (ch <= U16('9') && ch >= U16('0')) {
        return true;
    }

    return false;
}

int u16isalnum(const u16 ch) {
    return u16isalpha(ch) || u16isdigit(ch);
}

int u16isspecial(const u16 ch) {
    static Regex* regex = NULL;
    if (regex == NULL) {
        regex = RegexCompile(U16("[@_!#$%^&*()<>?/\|}{~:]"));
    }

    u16 str[2] = { ch, '\0' };

    return RegexMatch(regex, str) != -1;
}

int u16atoi(const u16* ch) {
    int value = 0;
    int positive = 1;
    if (*ch == '\0') {
        return 0;
    }

    if (*ch == '-') {
        positive = -1;
        ch += 1;
    }

    while (*ch) {
        if (*ch >= '0' && *ch <= '9') {
            value = value * 10 + (*ch - '0');
        }

        ch++;
    }

    return value * positive;
}