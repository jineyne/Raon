#ifndef __BACKENDDEFINES_H__
#define __BACKENDDEFINES_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

// this file contains the code for all operations, when each operation
// is called the state of the cpu, the ram arr, and the operand type is
// passed in. the 16 bit operand type is a bit field representing what
// types of the operands the instruction is called with.
//
// TYPE BIT FIELD 
//  _______________ _______________ _______________ _______________     
// |               |               |               |               |
// | 0 | R | M | L | 0 | R | M | L | 0 | R | M | L | 0 | R | M | L |
// |_______________|_______________|_______________|_______________|
//     operand 1       operand 2       operand 3       operand 4
//
// L = literal   - this means we want to use the operand literally -> val
// C = Constant  - this means we want to access constant at the operand -> constant[val]
// M = memory    - this means we want to access ram at the operand -> memory[val]
// R = reference - this means we want to register -> registers[ind]
//
// to convert the constants L, M, R to this format the OPERAND macro is used
#define OPERAND(o1, o2, o3, o4) ((o4 << 12) | (o3 << 8) | (o2 << 4) | o1)

#define GET_OP1(VAL) (VAL & 0xF)
#define GET_OP2(VAL) (VAL >> 4) & 0xF
#define GET_OP3(VAL) (VAL >> 8) & 0xF
#define GET_OP4(VAL) (VAL >> 12) & 0xF

typedef enum {
    L = 0x1, // Literal
    C = 0x2, // Constants
    M = 0x3, // Memory
    R = 0x4, // Register
} EOperand;

typedef enum {
    OP_NONE,    // NOTHING

    OP_HALT,    // STOP PROGRAM,
    OP_RET,     // POP VALUE FROM THE TOP OF THE STACK

    OP_MOVE,    // MOVE a b => b -> a

    OP_ADD,     // ADD r0 r1 r2 => r0 = r1 + r2
    OP_SUB,     // SUB r0 r1 r2 => r0 = r1 - r2
    OP_MUL,     // MUL r0 r1 r2 => r0 = r1 * r2
    OP_DIV,     // DIV r0 r1 r2 => r0 = r1 / r2
} EOpCode;

#ifdef __cplusplus
}
#endif

#endif // __BACKENDDEFINES_H__
