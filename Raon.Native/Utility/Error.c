#include "Error.h"

static int *gErrorList = ERROR_NONE;

static FErrorStringDesc gLocale[LOCALE_COUNT] = {
    {
        U16("구현되지 않은 기능입니다."),
        U16("인자 값이 올바르지 않습니다."),
        U16("내부 오류."),

        U16("'%s'는 올바르지 않은 토큰입니다."),
        U16("'%s'는 올바르지 않은 문법입니다."),

        U16("잘못된 파일 끝 입니다."),
        U16("'%s'는 잘못된 식별자입니다."),

        U16("'%s'는 중복되었습니다."),
        U16("'%s'을 찾을 수 없습니다."),

        U16("'%s'는 대입할 수 없는 값입니다."),
        U16("메모리 할당에 실패하였습니다."),
        U16("스택 오버플로우."),
        U16("스택 언더플로우."),
    }
};

int GetErrorCount() {
    return STACK_SIZE(gErrorList);
}

int GetError() {
    if (STACK_SIZE(gErrorList) <= 0) {
        return ERROR_NONE;
    }

    return STACK_POP(gErrorList);
}

void ClearError() {
    STACK_CLEAR(gErrorList);
}

void PushError(int type) {
    STACK_PUSH(gErrorList, type);
}

#define BUFFER_COUNT 1024

typedef enum {
    LEVEL_TRACE,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_FATAL,
} ELogLevel;

static const u16 *levelStrings[] = {
    U16("trace"), U16("debug"), U16("info"), U16("warning"), U16("error"), U16("fatal")
};

static const u16 *levelColors[] = {
    U16("\x1b[94m"), U16("\x1b[36m"), U16("\x1b[32m"), U16("\x1b[33m"), U16("\x1b[31m"), U16("\x1b[35m")
};

void printCompileLogPrefix(ELogLevel level, u16 *file, size_t line, size_t pos) {
    u16 buf[16];
    time_t t = time(NULL);
    struct tm tm;
    localtime_s(&tm, &t);

    buf[wcsftime(buf, sizeof(buf), U16("%H:%M:%S"), &tm)] = U16('\0');
    wprintf(U16("%s %s%-5s\x1b[0m \x1b[90m%s:(%lld, %lld):\x1b[0m "),
            buf, levelColors[level], levelStrings[level], file, line, pos);
}

void printeLogPrefix(ELogLevel level) {
    u16 buf[16];
    time_t t = time(NULL);
    struct tm tm;
    localtime_s(&tm, &t);

    buf[wcsftime(buf, sizeof(buf), U16("%H:%M:%S"), &tm)] = U16('\0');
    wprintf(U16("%s %s%-5s):\x1b[0m "), buf, levelColors[level], levelStrings[level]);
}

void CompileInfo(int type, u16 *file, size_t line, size_t pos, ...) {
    STACK_PUSH(gErrorList, type);
    printCompileLogPrefix(LEVEL_INFO, file, line, pos);

    u16 buffer[BUFFER_COUNT] = {0,};

    va_list varg;
    va_start(varg, pos);

    vswprintf(buffer, BUFFER_COUNT, GetErrorString(type), varg);
    buffer[u16len(buffer)] = '\n';

    wprintf(buffer);

    va_end(varg);
}

void CompileWarning(int type, u16 *file, size_t line, size_t pos, ...) {
    STACK_PUSH(gErrorList, type);
    printCompileLogPrefix(LEVEL_WARNING, file, line, pos);

    u16 buffer[BUFFER_COUNT] = {0,};

    va_list varg;
    va_start(varg, pos);

    vswprintf(buffer, BUFFER_COUNT, GetErrorString(type), varg);
    buffer[u16len(buffer)] = '\n';

    wprintf(buffer);

    va_end(varg);
}

void CompileError(int type, u16 *file, size_t line, size_t pos, ...) {
    STACK_PUSH(gErrorList, type);
    printCompileLogPrefix(LEVEL_ERROR, file, line, pos);

    u16 buffer[BUFFER_COUNT] = {0,};

    va_list varg;
    va_start(varg, pos);

    vswprintf(buffer, BUFFER_COUNT, GetErrorString(type), varg);
    buffer[u16len(buffer)] = '\n';

    wprintf(buffer);

    va_end(varg);
}

void Info(int type, ...) {
    STACK_PUSH(gErrorList, type);
    printeLogPrefix(LEVEL_INFO);

    u16 buffer[BUFFER_COUNT] = {0,};

    va_list varg;
    va_start(varg, type);

    vswprintf(buffer, BUFFER_COUNT, GetErrorString(type), varg);
    buffer[u16len(buffer)] = '\n';

    wprintf(buffer);

    va_end(varg);
}

void Warning(int type, ...) {
    STACK_PUSH(gErrorList, type);
    printeLogPrefix(LEVEL_WARNING);

    u16 buffer[BUFFER_COUNT] = {0,};

    va_list varg;
    va_start(varg, type);

    vswprintf(buffer, BUFFER_COUNT, GetErrorString(type), varg);
    buffer[u16len(buffer)] = '\n';

    wprintf(buffer);

    va_end(varg);
}

void Error(int type, ...) {
    STACK_PUSH(gErrorList, type);
    printeLogPrefix(LEVEL_ERROR);

    u16 buffer[BUFFER_COUNT] = {0,};

    va_list varg;
    va_start(varg, type);

    vswprintf(buffer, BUFFER_COUNT, GetErrorString(type), varg);
    buffer[u16len(buffer)] = '\n';

    wprintf(buffer);

    va_end(varg);
}

void Critical(int type, ...) {
    STACK_PUSH(gErrorList, type);
    printeLogPrefix(LEVEL_FATAL);

    u16 buffer[BUFFER_COUNT] = {0,};

    va_list varg;
    va_start(varg, type);

    vswprintf(buffer, BUFFER_COUNT, GetErrorString(type), varg);
    buffer[u16len(buffer)] = '\n';

    wprintf(buffer);

    va_end(varg);

    exit(type);
}

#define CASE(TYPE, MEMBER) case TYPE : return gLocale[currentLocale].MEMBER

u16 *GetErrorString(int type) {
    const ELocale currentLocale = GetLocale();

    switch (type) {
    CASE(ERROR_NOT_IMPLEMENT, notImplement);
    CASE(ERROR_ARGUMENT_NULL, argumentNull);

    CASE(ERROR_INVALID_TOKEN, invalidToken);
    CASE(ERROR_INVALID_SYNTAX, invalidSyntax);
    CASE(ERROR_INVALID_EOF, invalidEof);
    CASE(ERROR_INVALID_IDENTIFIER, invalidIdentifier);

    CASE(ERROR_SYMBOL_DUPLICATED, symbolDuplicated);
    CASE(ERROR_SYMBOL_NOT_FOUND, symbolNotFound);

    CASE(ERROR_RVALUE_NOT_POSITION_AT_LVALUE, rvalueNotPositionAtLValue);

    CASE(ERROR_ALLOC_FAIL, allocFailed);

    CASE(ERROR_STACK_OVERFLOW, stackOverflow);
    CASE(ERROR_STACK_UNDERFLOW, stackUnderflow);

    default:
        return U16("");
    }
}
