#include "Regex.h"

#define MAX_REGEXP_OBJECTS      30    /* Max number of regex symbols in expression. */
#define MAX_CHAR_CLASS_LEN      40    /* Max length of character-class buffer in.   */

enum {
    UNUSED,
    DOT,
    BEGIN,
    END,
    QUESTIONMARK,
    STAR,
    PLUS,
    CHAR,
    CHAR_CLASS,
    INV_CHAR_CLASS,
    DIGIT,
    NOT_DIGIT,
    ALPHA,
    NOT_ALPHA,
    WHITESPACE,
    NOT_WHITESPACE,
    /* BRANCH */
};

typedef struct regex {
    unsigned char type;    //< CHAR, STAR, etc.
    union {
        u16 ch;  //< the character itself             
        u16* ccl; //< OR  a pointer to characters in class
    };
} Regex;

static int matchpattern(Regex* pattern, const u16* text);
static int matchcharclass(u16 c, const u16* str);
static int matchstar(Regex p, Regex* pattern, const u16* text);
static int matchplus(Regex p, Regex* pattern, const u16* text);
static int matchone(Regex p, u16 c);
static int matchmetachar(u16 c, const u16* str);
static int matchrange(u16 c, const u16* str);
static int ismetachar(u16 c);

Regex* RegexCompile(const u16* pattern) {
    static Regex re_compiled[MAX_REGEXP_OBJECTS];
    static u16 ccl_buf[MAX_CHAR_CLASS_LEN];
    int ccl_bufidx = 1;

    u16 c;     /* current u16 in pattern   */
    int i = 0;  /* index into pattern        */
    int j = 0;  /* index into re_compiled    */

    while (pattern[i] != '\0' && (j + 1 < MAX_REGEXP_OBJECTS)) {
        c = pattern[i];

        switch (c) {
            /* Meta-characters: */
        case '^': { re_compiled[j].type = BEGIN; } break;
        case '$': { re_compiled[j].type = END; } break;
        case '.': { re_compiled[j].type = DOT; } break;
        case '*': { re_compiled[j].type = STAR; } break;
        case '+': { re_compiled[j].type = PLUS; } break;
        case '?': { re_compiled[j].type = QUESTIONMARK; } break;
            /*    case '|': {    re_compiled[j].type = BRANCH;          } break; <-- not working properly */

                  /* Escaped character-classes (\s \w ...): */
        case '\\':
        {
            if (pattern[i + 1] != '\0') {
                /* Skip the escape-u16 '\\' */
                i += 1;
                /* ... and check the next */
                switch (pattern[i]) {
                    /* Meta-character: */
                case 'd': { re_compiled[j].type = DIGIT; } break;
                case 'D': { re_compiled[j].type = NOT_DIGIT; } break;
                case 'w': { re_compiled[j].type = ALPHA; } break;
                case 'W': { re_compiled[j].type = NOT_ALPHA; } break;
                case 's': { re_compiled[j].type = WHITESPACE; } break;
                case 'S': { re_compiled[j].type = NOT_WHITESPACE; } break;

                    /* Escaped character, e.g. '.' or '$' */
                default:
                {
                    re_compiled[j].type = CHAR;
                    re_compiled[j].ch = pattern[i];
                } break;
                }
            }
            /* '\\' as last u16 in pattern -> invalid regular expression. */
    /*
            else
            {
              re_compiled[j].type = CHAR;
              re_compiled[j].ch = pattern[i];
            }
    */
        } break;

        /* Character class: */
        case '[':
        {
            /* Remember where the char-buffer starts. */
            int buf_begin = ccl_bufidx;

            /* Look-ahead to determine if negated */
            if (pattern[i + 1] == '^') {
                re_compiled[j].type = INV_CHAR_CLASS;
                i += 1; /* Increment i to avoid including '^' in the char-buffer */
            }
            else {
                re_compiled[j].type = CHAR_CLASS;
            }

            /* Copy characters inside [..] to buffer */
            while ((pattern[++i] != ']')
                && (pattern[i] != '\0')) /* Missing ] */
            {
                if (pattern[i] == '\\') {
                    if (ccl_bufidx >= MAX_CHAR_CLASS_LEN - 1) {
                        //fputs("exceeded internal buffer!\n", stderr);
                        return 0;
                    }
                    ccl_buf[ccl_bufidx++] = pattern[i++];
                }
                else if (ccl_bufidx >= MAX_CHAR_CLASS_LEN) {
                    //fputs("exceeded internal buffer!\n", stderr);
                    return 0;
                }
                ccl_buf[ccl_bufidx++] = pattern[i];
            }
            if (ccl_bufidx >= MAX_CHAR_CLASS_LEN) {
                /* Catches cases such as [00000000000000000000000000000000000000][ */
                //fputs("exceeded internal buffer!\n", stderr);
                return 0;
            }
            /* Null-terminate string end */
            ccl_buf[ccl_bufidx++] = 0;
            re_compiled[j].ccl = &ccl_buf[buf_begin];
        } break;

        /* Other characters: */
        default:
        {
            re_compiled[j].type = CHAR;
            re_compiled[j].ch = c;
        } break;
        }
        i += 1;
        j += 1;
    }
    /* 'UNUSED' is a sentinel used to indicate end-of-pattern */
    re_compiled[j].type = UNUSED;

    return (Regex*)re_compiled;
}

int RegexMatch(Regex* pattern, const u16* text) {
    if (pattern != 0) {
        if (pattern[0].type == BEGIN) {
            return ((matchpattern(&pattern[1], text)) ? 0 : -1);
        }
        else {
            int idx = -1;

            do {
                idx += 1;

                if (matchpattern(pattern, text)) {
                    if (text[0] == '\0')
                        return -1;

                    return idx;
                }
            } while (*text++ != '\0');
        }
    }
    return -1;
}

int RegexMatchPattern(const u16* pattern, const u16* text) {
    return RegexMatch(RegexCompile(pattern), text);
}

static int matchrange(u16 c, const u16* str) {
    return ((c != '-') && (str[0] != '\0') && (str[0] != '-') &&
        (str[1] == '-') && (str[1] != '\0') &&
        (str[2] != '\0') && ((c >= str[0]) && (c <= str[2])));
}
static int ismetachar(u16 c) {
    return ((c == 's') || (c == 'S') || (c == 'w') || (c == 'W') || (c == 'd') || (c == 'D'));
}

static int matchmetachar(u16 c, const u16* str) {
    switch (str[0]) {
    case 'd': return  u16isdigit(c);
    case 'D': return !u16isdigit(c);
    case 'w': return  u16isalnum(c);
    case 'W': return !u16isalnum(c);
    case 's': return  u16isspace(c);
    case 'S': return !u16isspace(c);
    default:  return (c == str[0]);
    }
}

static int matchcharclass(u16 c, const u16* str) {
    do {
        if (matchrange(c, str)) {
            return 1;
        }
        else if (str[0] == '\\') {
            /* Escape-char: increment str-ptr and match on next u16 */
            str += 1;
            if (matchmetachar(c, str)) {
                return 1;
            }
            else if ((c == str[0]) && !ismetachar(c)) {
                return 1;
            }
        }
        else if (c == str[0]) {
            if (c == '-') {
                return ((str[-1] == '\0') || (str[1] == '\0'));
            }
            else {
                return 1;
            }
        }
    } while (*str++ != '\0');

    return 0;
}

static int matchone(Regex p, u16 c) {
    switch (p.type) {
    case DOT:            return 1;
    case CHAR_CLASS:     return  matchcharclass(c, (const u16*)p.ccl);
    case INV_CHAR_CLASS: return !matchcharclass(c, (const u16*)p.ccl);
    case DIGIT:          return  u16isdigit(c);
    case NOT_DIGIT:      return !u16isdigit(c);
    case ALPHA:          return  u16isalnum(c);
    case NOT_ALPHA:      return !u16isalnum(c);
    case WHITESPACE:     return  u16isspace(c);
    case NOT_WHITESPACE: return !u16isspace(c);
    default:             return  (p.ch == c);
    }
}

static int matchstar(Regex p, Regex* pattern, const u16* text) {
    do {
        if (matchpattern(pattern, text))
            return 1;
    } while ((text[0] != '\0') && matchone(p, *text++));

    return 0;
}

static int matchplus(Regex p, Regex* pattern, const u16* text) {
    while ((text[0] != '\0') && matchone(p, *text++)) {
        if (matchpattern(pattern, text))
            return 1;
    }
    return 0;
}

static int matchquestion(Regex p, Regex* pattern, const u16* text) {
    if (p.type == UNUSED)
        return 1;
    if (matchpattern(pattern, text))
        return 1;
    if (*text && matchone(p, *text++))
        return matchpattern(pattern, text);
    return 0;
}

static int matchpattern(Regex* pattern, const u16* text) {
    do {
        if ((pattern[0].type == UNUSED) || (pattern[1].type == QUESTIONMARK)) {
            return matchquestion(pattern[0], &pattern[2], text);
        }
        else if (pattern[1].type == STAR) {
            return matchstar(pattern[0], &pattern[2], text);
        }
        else if (pattern[1].type == PLUS) {
            return matchplus(pattern[0], &pattern[2], text);
        }
        else if ((pattern[0].type == END) && pattern[1].type == UNUSED) {
            return (text[0] == '\0');
        }
    } while ((text[0] != '\0') && matchone(*pattern++, *text++));

    return 0;
}