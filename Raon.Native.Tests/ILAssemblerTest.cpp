#include "pch.h"

#include "FrontEnd/Parser.h"
#include "FrontEnd/SyntaxAnalyzer.h"
#include "IL/ILBase.h"
#include "IL/ILAssembler.h"
#include "Utility/Error.h"

TEST(ILAssemblerTest, Global) {
    ClearError();

    FParser *parser = nullptr;
    FBaseNode *node = nullptr;

    FSyntaxAnalyzer *analyzer = nullptr;
    EXPECT_NO_THROW(analyzer = CreateSyntaxAnalyzer(NULL));

    FILAssembler *assembler = nullptr;
    EXPECT_NO_THROW(assembler = CreateILAssembler());


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

        /*PrintNode(node);
        wprintf(L"\n\n");*/

        assembler->local = analyzer->symtab;
        EXPECT_TRUE(ILGenerate(assembler, node));

        FStmt *it;
        ARRAY_FOREACH(assembler->statements, it) {
            FreeIL(reinterpret_cast<FILBase*>(it));
        }

        EXPECT_NO_THROW(FreeNode(node));
        EXPECT_NO_THROW(FreeParser(parser));
    }

    EXPECT_NO_THROW(FreeSyntaxAnalyzer(analyzer));
    EXPECT_NO_THROW(FreeILAssembler(assembler));
}
