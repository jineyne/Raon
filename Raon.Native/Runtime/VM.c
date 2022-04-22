#include "VM.h"
#include "Instruction.h"

FVM *CreateVM() {
    FVM *vm = malloc(sizeof(FVM));

    vm->object = NULL;

    vm->stacks = NULL;
    vm->memory = NULL;

    vm->running = false;
    for (int i = 0; i < 16; i++) {
        vm->registers[i].type = VALUE_NONE;
        vm->registers[i].data = 0;
    }

    memset(vm->registers, 0, sizeof(vm->registers));

    return vm;
}

void FreeVM(FVM *vm) {
    // ARRAY_FREE(vm->object);

    ARRAY_FREE(vm->memory);
    STACK_FREE(vm->stacks);
}

extern FOp ops[];

#define FETCH() this->object->codes[this->pc++]

void Execute(FVM *this, FCompilerObject *object) {
    this->object = object;

    uint64_t opcode = 0;
    uint16_t operation = 0, operands = 0;

    this->pc = 0;
    this->running = true;

    while (this->running) {
        opcode = FETCH();
        operation = (uint16_t) opcode;
        operands = opcode >> 16;

        // debug?

        this->running = ops[operation].func(this, operands);
    }

    this->object = NULL;
}
