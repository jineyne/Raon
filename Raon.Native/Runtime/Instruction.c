#include "Instruction.h"

#include "Utility/Converter.h"
#include "Utility/Error.h"

#define FETCH() this->object->codes[this->pc++]
#define MV(DST, SRC) memcpy(&DST, &SRC, sizeof(FValue))

#define GET_OP(AT, SRC, ADDR) switch (GET_OP##AT##(type)) {     \
    case B: SRC.type = VALUE_BOOL; SRC.data = ADDR; break;      \
    case L: SRC.type = VALUE_INT; SRC.data = ADDR; break;       \
    case C: SRC = this->object->constants[ADDR]; break;         \
    case M: SRC = this->memory[ADDR]; break;                    \
    case R: SRC = this->registers[ADDR]; break;                 \
    default: return false;                                      \
}

static bool nop(FVM *this, uint16_t type) {
    return true;
}

static bool halt(FVM *this, uint16_t type) {
    return false;
}

static bool ret(FVM *this, uint16_t type) {
    return true;
}

static bool move(FVM *this, uint16_t type) {
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *src = NULL;

    switch (type) {
    case OPERAND(M, B, 0, 0):
        this->memory[val1].type = VALUE_BOOL;
        this->memory[val1].data = val2;
        break;

    case OPERAND(M, L, 0, 0):
        this->memory[val1].type = VALUE_INT;
        this->memory[val1].data = val2;
        break;

    case OPERAND(M, C, 0, 0):
        MV(this->memory[val1], this->object->constants[val2]);
        break;

    case OPERAND(M, M, 0, 0):
        MV(this->memory[val1], this->memory[val2]);
        break;

    case OPERAND(M, S, 0, 0):
        MV(this->memory[val1], this->stacks[val2]);
        break;

    case OPERAND(M, R, 0, 0):
        MV(this->memory[val1], this->registers[val2]);
        break;

    case OPERAND(R, B, 0, 0):
        this->registers[val1].type = VALUE_BOOL;
        this->registers[val1].data = val2;
        break;

    case OPERAND(R, L, 0, 0):
        this->registers[val1].type = VALUE_INT;
        this->registers[val1].data = val2;
        break;

    case OPERAND(R, C, 0, 0):
        MV(this->registers[val1], this->object->constants[val2]);
        break;

    case OPERAND(R, M, 0, 0):
        MV(this->registers[val1], this->memory[val2]);
        break;

    case OPERAND(R, S, 0, 0):
        MV(this->registers[val1], this->stacks[val2]);
        break;

    case OPERAND(R, R, 0, 0):
        MV(this->registers[val1], this->registers[val2]);
        break;

    case OPERAND(S, B, 0, 0):
        this->stacks[val1].type = VALUE_BOOL;
        this->stacks[val1].data = val2;
        break;

    case OPERAND(S, L, 0, 0):
        this->stacks[val1].type = VALUE_INT;
        this->stacks[val1].data = val2;
        break;

    case OPERAND(S, C, 0, 0):
        MV(this->stacks[val1], this->object->constants[val2]);
        break;

    case OPERAND(S, M, 0, 0):
        MV(this->stacks[val1], this->memory[val2]);
        break;

    case OPERAND(S, S, 0, 0):
        MV(this->stacks[val1], this->stacks[val2]);
        break;

    case OPERAND(S, R, 0, 0):
        MV(this->stacks[val1], this->registers[val2]);
        break;

    default:
        return false;
    }

    return true;
}

#define BINOP(OP)                                                       \
    if (src1.type != src2.type) { Critical(ERROR_CASTING_FAIL); }       \
    FConverter16 cvts1; FConverter16 cvts2; FConverter16 cvts3;         \
    dst->type = src1.type;                                              \
    switch (dst->type) {                                                \
    case VALUE_INT: dst->data = src1.data OP src2.data; break;          \
    case VALUE_REAL:                                                    \
        cvts1.integer = src1.data; cvts2.integer = src2.data;           \
        cvts3.real = cvts1.real OP cvts2.real;                          \
        dst->data = cvts3.integer;                                      \
        break;                                                          \
    default: Critical(ERROR_OPERAND_NOT_SUPPORT); return false;         \
    }

#define BOOLOP(OP)                                                      \
    if (src1.type != src2.type) { Critical(ERROR_CASTING_FAIL); }       \
    FConverter16 cvts1; FConverter16 cvts2;                             \
    dst->type = VALUE_BOOL;                                             \
    switch (dst->type) {                                                \
    case VALUE_BOOL: dst->data = src1.data OP src2.data; break;         \
    case VALUE_INT: dst->data = src1.data OP src2.data; break;          \
    case VALUE_REAL:                                                    \
        cvts1.integer = src1.data; cvts2.integer = src2.data;           \
        dst->data = cvts1.real OP cvts2.real;                           \
        break;                                                          \
    default: Critical(ERROR_OPERAND_NOT_SUPPORT); return false;         \
    }

static bool add(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    BINOP(+)

    return true;
}

static bool sub(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    BINOP(-)

    return true;
}

static bool mul(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    BINOP(*)

    return true;
}

static bool _div(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    if (src1.type != src2.type) {
        Critical(ERROR_CASTING_FAIL);
    }

    BINOP(/)

    return true;
}

static bool lt(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    BOOLOP(<)

    return true;
}

static bool lte(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    BOOLOP(<=)

    return true;
}

static bool gt(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    BOOLOP(>)

    return true;
}

static bool gte(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    BOOLOP(>=)

    return true;
}

static bool almosteq(double a, double b) {
    return (fabs(a - b) < (DBL_EPSILON * fabs(a + b)));
}

static bool eq(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    if (src1.type != src2.type) {
        Critical(ERROR_CASTING_FAIL);
    }

    FConverter16 cvts1;
    FConverter16 cvts2;

    dst->type = VALUE_BOOL;
    switch (dst->type) {
    case VALUE_BOOL:
        dst->data = src1.data == src2.data;
        break;
    case VALUE_INT:
        dst->data = src1.data == src2.data;
        break;
    case VALUE_REAL: cvts1.integer = src1.data;
        cvts2.integer = src2.data;
        dst->data = almosteq(cvts1.real, cvts2.real);
        break;
    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    return true;
}

static bool neq(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    if (src1.type != src2.type) {
        Critical(ERROR_CASTING_FAIL);
    }

    FConverter16 cvts1;
    FConverter16 cvts2;

    dst->type = VALUE_BOOL;
    switch (dst->type) {
    case VALUE_BOOL:
        dst->data = src1.data != src2.data;
        break;
    case VALUE_INT:
        dst->data = src1.data != src2.data;
        break;
    case VALUE_REAL:
        cvts1.integer = src1.data;
        cvts2.integer = src2.data;
        dst->data = !almosteq(cvts1.real, cvts2.real);
        break;
    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    return true;
}

static bool and(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    dst->data = src1.data && src2.data;

    return true;
}

static bool or(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        return false;
    }

    FValue src1 = {VALUE_NONE, 0};
    GET_OP(2, src1, val1);

    FValue src2 = {VALUE_NONE, 0};
    GET_OP(3, src2, val2);

    dst->data = src1.data || src2.data;

    return true;
}

FOp ops[] = {
    {0, U16("nop"), nop},

    {0, U16("halt"), halt},
    {0, U16("ret"), ret},

    {2, U16("move"), move},

    {3, U16("add"), add},
    {3, U16("sub"), sub},
    {3, U16("mul"), mul},
    {3, U16("div"), _div},

    {3, U16("lt"), lt},
    {3, U16("lte"), lte},
    {3, U16("gt"), gt},
    {3, U16("gte"), gte},
    {3, U16("eq"), eq},
    {3, U16("neq"), neq},
    {3, U16("and"), and},
    {3, U16("or"), or},
};
