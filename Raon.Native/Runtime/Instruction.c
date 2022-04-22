#include "Instruction.h"

#define FETCH() this->object->codes[this->pc++]
#define MV(DST, SRC) memcpy(&DST, &SRC, sizeof(FValue))

#define GET_OP(AT, SRC, ADDR) switch (GET_OP##AT##(type)) { \
    case L: SRC.type = VALUE_INT; SRC.data = ADDR; break; \
    case C: SRC = this->object->constants[ADDR]; break; \
    case M: SRC = this->memory[ADDR]; break; \
    case R: SRC = this->registers[ADDR]; break; \
    default: return false; \
}

static void checkMem(FVM *this, int64_t addr) {
    while (ARRAY_SIZE(this->memory) <= addr) {
        ARRAY_RESIZE(this->memory, 1 + ARRAY_CAPACITY(this->memory) * 2);
    }
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
    case OPERAND(M, L, 0, 0):
        checkMem(this, val1);
        this->memory[val1].type = VALUE_INT;
        this->memory[val1].data = val2;
        break;

    case OPERAND(M, C, 0, 0):
        checkMem(this, val1);
        MV(this->memory[val1], this->object->constants[val2]);
        break;

    case OPERAND(M, M, 0, 0):
        checkMem(this, val1);
        MV(this->memory[val1], this->memory[val2]);
        break;

    case OPERAND(M, R, 0, 0):
        checkMem(this, val1);
        MV(this->memory[val1], this->registers[val2]);
        break;

    case OPERAND(R, L, 0, 0):
        this->registers[val1].type = VALUE_INT;
        this->registers[val1].data = val2;
        break;

    case OPERAND(R, C, 0, 0):
        MV(this->registers[val1], this->object->constants[val2]);
        break;

    case OPERAND(R, M, 0, 0):
        checkMem(this, val2);
        MV(this->registers[val1], this->memory[val2]);
        break;

    case OPERAND(R, R, 0, 0):
        MV(this->registers[val1], this->registers[val2]);
        break;

    default:
        return false;
    }

    return true;
}

static bool add(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case M:
        checkMem(this, dstOp);
        dst = &this->memory[dstOp];
        break;

    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        return false;
    }

    FValue src1 = { VALUE_NONE, 0 };
    GET_OP(2, src1, val1);

    FValue src2 = { VALUE_NONE, 0 };
    GET_OP(3, src2, val2);

    if (src1.type == src2.type) {
        dst->type = src1.type;
        switch (dst->type) {
        case VALUE_INT:
            dst->data = src1.data + src2.data;
            break;

        case VALUE_DOUBLE:
            dst->data = (int64_t) ((double) src1.data + (double) src2.data);
            break;

        default:
            return false;
        }
    }

    return true;
}

static bool sub(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case M:
        checkMem(this, dstOp);
        dst = &this->memory[dstOp];
        break;

    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        return false;
    }

    FValue src1 = { VALUE_NONE, 0 };
    GET_OP(2, src1, val1);

    FValue src2 = { VALUE_NONE, 0 };
    GET_OP(3, src2, val2);

    if (src1.type == src2.type) {
        dst->type = src1.type;
        switch (dst->type) {
        case VALUE_INT:
            dst->data = src1.data - src2.data;
            break;

        case VALUE_DOUBLE:
            dst->data = (int64_t) ((double) src1.data - (double) src2.data);
            break;

        default:
            return false;
        }
    }

    return true;
}

static bool mul(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case M:
        checkMem(this, dstOp);
        dst = &this->memory[dstOp];
        break;

    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        return false;
    }

    FValue src1 = { VALUE_NONE, 0 };
    GET_OP(2, src1, val1);

    FValue src2 = { VALUE_NONE, 0 };
    GET_OP(3, src2, val2);

    if (src1.type == src2.type) {
        dst->type = src1.type;
        switch (dst->type) {
        case VALUE_INT:
            dst->data = src1.data * src2.data;
            break;

        case VALUE_DOUBLE:
            dst->data = (int64_t) ((double) src1.data * (double) src2.data);
            break;

        default:
            return false;
        }
    }

    return true;
}

static bool _div(FVM *this, uint16_t type) {
    int64_t dstOp = FETCH();
    int64_t val1 = FETCH();
    int64_t val2 = FETCH();

    FValue *dst = NULL;
    switch (GET_OP1(type)) {
    case M:
        checkMem(this, dstOp);
        dst = &this->memory[dstOp];
        break;

    case R:
        dst = &this->registers[dstOp];
        break;

    default:
        return false;
    }

    FValue src1 = { VALUE_NONE, 0 };
    GET_OP(2, src1, val1);

    FValue src2 = { VALUE_NONE, 0 };
    GET_OP(3, src2, val2);

    if (src1.type == src2.type) {
        dst->type = src1.type;
        switch (dst->type) {
        case VALUE_INT:
            dst->data = src1.data / src2.data;
            break;

        case VALUE_DOUBLE:
            dst->data = (int64_t) ((double) src1.data / (double) src2.data);
            break;

        default:
            return false;
        }
    }

    return true;
}

FOp ops[] = {
    { 0, U16("nop"), nop },

    { 0, U16("halt"), halt },
    { 0, U16("ret"), ret },

    { 2, U16("move"), move },

    { 3, U16("add"), add },
    { 3, U16("sub"), sub },
    { 3, U16("mul"), mul },
    { 3, U16("div"), _div },
};