#ifndef __BACKENDDEFINES_H__
#define __BACKENDDEFINES_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif


// L = literal   - this means we want to use the operand literally -> val
// L = literal   - this means we want to use the operand literally -> val
// L = literal   - this means we want to use the operand literally -> val
// C = Constant  - this means we want to access constant at the operand -> constant[val]
// M = memory    - this means we want to access memory at the operand -> memory[val]
// S = stack     - this means we want to access stack at the operand -> stack[val]
// R = reference - this means we want to register -> registers[ind]
#define OPERAND(o1, o2, o3, o4) ((o4 << 12) | (o3 << 8) | (o2 << 4) | o1)

#define GET_OP1(VAL) (VAL & 0xF)
#define GET_OP2(VAL) (VAL >> 4) & 0xF
#define GET_OP3(VAL) (VAL >> 8) & 0xF
#define GET_OP4(VAL) (VAL >> 12) & 0xF

typedef enum {
    // Byte (Bool, Byte)
    B = 0x1,
    // Int
    L = 0x2,
    // Constants
    C = 0x3,

    // Memory
    M = 0x4,
    // Stack
    S = 0x5,
    // Register
    R = 0x6,
} EOperand;

typedef enum {
    REG_0 = 0,
    REG_1,
    REG_2,
    REG_3,
    REG_4,
    REG_5,
    REG_6,
    REG_7,

    REG_ZF,

    REG_COUNT,
};

typedef enum {
    // NOTHING
    OP_NONE,

    // STOP PROGRAM,
    OP_HALT,
    // POP VALUE FROM THE TOP OF THE STACK
    OP_RET,

    // MOVE a b => b -> a
    OP_MOVE,

    // ADD r0 r1 r2 => r0 = r1 + r2
    OP_ADD,
    // SUB r0 r1 r2 => r0 = r1 - r2
    OP_SUB,
    // MUL r0 r1 r2 => r0 = r1 * r2
    OP_MUL,
    // DIV r0 r1 r2 => r0 = r1 / r2
    OP_DIV,

    // AND r0 r1 r2 => r0 = r1 && r2
    OP_AND,
    // OR r0 r1 r2 => r0 = r1 || r2
    OP_OR,

    // COMPARE r0 r1
    // r0 - r1
    // 1. r0 > r1 => ZF = 1
    // 2. r0 < r1 => ZF = -1
    // 3. r0 = r1 => ZF = 0
    OP_CMP,

    // ZF == 1
    OP_JA,
    // ZF >= 0
    OP_JAE,
    // ZF == -1
    OP_JB,
    // ZF <= 0
    OP_JBE,
    // ZF == 0
    OP_JE,
    // ZF != 0
    OP_JNE,
    // ZF == 0
    OP_JZ,
    // ZF != 0
    OP_JNZ,
} EOpCode;

#ifdef __cplusplus
}
#endif

#endif // __BACKENDDEFINES_H__
