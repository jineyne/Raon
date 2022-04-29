#include "pch.h"

#include "FrontEnd/Parser.h"
#include "FrontEnd/SyntaxAnalyzer.h"
#include "BackEnd/Compiler.h"
#include "IL/ILAssembler.h"
#include "Utility/Error.h"

TEST(CompilerTest, Global) {
    InitRaon();

    FParser *parser = nullptr;
    FBaseNode *node = nullptr;

    FSyntaxAnalyzer *analyzer = nullptr;
    EXPECT_NO_THROW(analyzer = CreateSyntaxAnalyzer(NULL));

    FILAssembler *assembler = nullptr;
    EXPECT_NO_THROW(assembler = CreateILAssembler());

    FCompiler *compiler = nullptr;
    EXPECT_NO_THROW(compiler = CreateCompiler());


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

        EXPECT_NO_THROW(FreeNode(node));
        EXPECT_NO_THROW(FreeParser(parser));
    }

    EXPECT_NO_THROW(FreeCompiler(compiler));
    EXPECT_NO_THROW(FreeSyntaxAnalyzer(analyzer));
    EXPECT_NO_THROW(FreeILAssembler(assembler));
}
