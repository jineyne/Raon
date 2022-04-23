#include "pch.h"

#include "FrontEnd/Parser.h"
#include "FrontEnd/SyntaxAnalyzer.h"
#include "BackEnd/Compiler.h"
#include "Runtime/VM.h"
#include "IL/FILAssembler.h"
#include "Utility/Error.h"

TEST(VMTest, Global) {
    SetLocale(LOCALE_KO);
    ClearError();


    FParser *parser = nullptr;
    FBaseNode *node = nullptr;

    FSyntaxAnalyzer *analyzer = nullptr;
    EXPECT_NO_THROW(analyzer = CreateSyntaxAnalyzer(NULL));

    FILAssembler *assembler = nullptr;
    EXPECT_NO_THROW(assembler = CreateILAssembler());

    FCompiler *compiler = nullptr;
    EXPECT_NO_THROW(compiler = CreateCompiler());

    FVM *vm = nullptr;
    EXPECT_NO_THROW(vm = CreateVM());


    {
        u16 *src = U16(R"(
a = (10 + 2) * 4 - 7
b = 1 / a
)");
        EXPECT_NO_THROW(parser = CreateParserFromMemory(src));
        EXPECT_NO_THROW(node = Parse(parser));


        EXPECT_EQ(GetErrorCount(), 0);
        EXPECT_EQ(node->type, AST_COMPOUND);

        bool success = false;
        EXPECT_NO_THROW(success = RunSyntaxAnalyzer(analyzer, node));
        EXPECT_TRUE(success);

        assembler->local = analyzer->symtab;

        FILBase *il = nullptr;
        EXPECT_NO_THROW(il = ILGenerate(assembler, node));

        FCompilerObject *object = CompileIL(compiler, il);
        EXPECT_NO_THROW(FreeIL(il));

        Execute(vm, object);

        EXPECT_EQ(vm->memory[0].data, 41);
        EXPECT_EQ(vm->memory[1].data, 0);

        FreeCompilerObject(object);

        EXPECT_NO_THROW(FreeNode(node));
        EXPECT_NO_THROW(FreeParser(parser));
    }

    EXPECT_NO_THROW(FreeVM(vm));
    EXPECT_NO_THROW(FreeCompiler(compiler));
    EXPECT_NO_THROW(FreeSyntaxAnalyzer(analyzer));
    EXPECT_NO_THROW(FreeILAssembler(assembler));
}

TEST(VMTest, Interpret) {
    FVM *vm = CreateVM();

    ExecuteSource(vm, U16("a = 10 * 6 - 7 * 13"));
    EXPECT_EQ(GetErrorCount(), 0);

    ExecuteSource(vm, U16("b = a * 10\nb = a * c"));
    EXPECT_EQ(GetErrorCount(), 1);

    ExecuteSource(vm, U16("b = a * 10;"));
    EXPECT_EQ(GetErrorCount(), 1);

    FreeVM(vm);
}
