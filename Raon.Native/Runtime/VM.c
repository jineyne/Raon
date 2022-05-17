#include "VM.h"
#include "Instruction.h"
#include "BackEnd/Compiler.h"
#include "FrontEnd/Lexer.h"
#include "FrontEnd/Parser.h"
#include "FrontEnd/SyntaxAnalyzer.h"
#include "Symbol/SymbolTable.h"
#include "Utility/Error.h"

FVM *CreateVM() {
    FVM *vm = malloc(sizeof(FVM));

    vm->object = NULL;

    /*vm->stacks = NULL;
    vm->memory = NULL;*/

    memset(vm->stacks, 0, sizeof(vm->stacks));
    memset(vm->memory, 0, sizeof(vm->memory));

    vm->running = false;
    for (int i = 0; i < REG_COUNT; i++) {
        vm->registers[i].type = VALUE_NONE;
        vm->registers[i].data = 0;
    }
    vm->global = CreateSymbolTable(U16("VM"), NULL);

    memset(vm->registers, 0, sizeof(vm->registers));

    return vm;
}

void FreeVM(FVM *vm) {
    // ARRAY_FREE(vm->object);

    /*ARRAY_FREE(vm->memory);
    STACK_FREE(vm->stacks);*/
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

void ExecuteSource(FVM *vm, u16 *str) {
    ClearError();

    FParser *parser = CreateParserFromMemory(str);

    FBaseNode *node = Parse(parser);
    if (node == NULL || GetErrorCount() != 0) {
        goto finit0;
    }

    FSyntaxAnalyzer *analyzer = CreateSyntaxAnalyzer(CopySymbolTable(U16("SyntaxAnalyzer"), vm->global));
    if (!RunSyntaxAnalyzer(analyzer, node)) {
        goto finit1;
    }

    ApplyAndFreeSymbolTable(vm->global, analyzer->symtab, false);
    FILAssembler *assembler = CreateILAssembler();
    assembler->local = vm->global;

    FILBase *il = ILGenerate(assembler, node);
    if (il == NULL) {
        goto finit2;
    }

    analyzer->symtab = NULL;

    FCompiler *compiler = CreateCompiler();
    FCompilerObject *object = CompileIL(compiler, il);
    if (object == NULL) {
        goto finit3;
    }

    Execute(vm, object);

finit3:
    FreeCompilerObject(object);
    FreeCompiler(compiler);

finit2:
    FreeIL(il);
    FreeILAssembler(assembler);

finit1:
    FreeSyntaxAnalyzer(analyzer);

finit0:
    FreeNode(node);
    FreeParser(parser);
}


void InterpretLine(FVM *vm, FString *line) {
    ExecuteSource(vm, line->data);
}

bool TryGetBoolValueByName(FVM *vm, u16 *name, bool *out) {
    FString str = {name, u16len(name)};
    FSymbol *symbol = NULL;

    *out = false;

    if (FindSymbol(vm, &str, &symbol) != ERROR_NONE) {
        return false;
    }

    if (symbol == NULL) {
        return false;
    }

    if (symbol->slot < 0) {
        return false;
    }

    if (vm->memory[symbol->slot].type != VALUE_BOOL) {
        return false;
    }

    *out = vm->memory[symbol->slot].data;
    return true;
}

bool TryGetIntegerValueByName(FVM *vm, u16 *name, int *out) {
    return false;
}

bool TryGetRealValueByName(FVM *vm, u16 *name, double *out) {
    return false;
}

bool TryGetStringValueByName(FVM *vm, u16 *name, u16 **out) {
    return false;
}
