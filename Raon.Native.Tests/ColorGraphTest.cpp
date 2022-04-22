#include "pch.h"

#include "AST/AST.h"
#include "FrontEnd/Parser.h"
#include "FrontEnd/ColorGraph.h"

class ColorGraphVisiter : public ASTVisiter<bool> {
private:
    ColorGraph *graph;

public:
    ColorGraphVisiter() {
        graph = CreateColorGraph();
    }

    ~ColorGraphVisiter() {
        FreeColorGraph(graph);
    }

    int getPosition(FBaseNode *node) {
        return GetColorFromGraph(graph, node);
    }

protected:
    bool visitAssignOpNode(FAssignOpNode *node) override {
        ClearColorGraph(graph);

        auto left = visit(node->left);
        auto right = visit(node->right);

        if (!left || !right) {
            return false;
        }

        // AddEdgeToGraph(graph, left, right);
        GreedyGraph(graph);

        // CHECK COLOR_GRAPH
        return true;
    }

    bool visitBinOpNode(FBinOpNode *node) override {
        auto left = visit(node->left);
        auto right = visit(node->right);

        if (!left || !right) {
            return false;
        }

        AddEdgeToGraph(graph, (FBaseNode *) node, node->left);
        AddEdgeToGraph(graph, (FBaseNode *) node, node->right);
        AddEdgeToGraph(graph, node->left, node->right);

        return true;
    }

    bool visitCompoundNode(FCompoundNode *node) override {
        FBaseNode *it;
        ARRAY_FOREACH(node->children, it) {
            visit(it);
        }

        return true;
    }

    bool visitIntegerNode(FIntegerNode *node) override {
        return true;
    }

    bool visitRealNode(FRealNode *node) override {
        return true;
    }

    bool visitStringNode(FStringNode *node) override {
        return true;
    }

    bool visitUnaryOpNode(FUnaryOpNode *node) override {
        return visit(node->expr);
    }

    bool visitVarNode(FVarNode *node) override {
        return true;
    }

    bool visitEmptyNode(FEmptyNode *node) override {
        return true;
    }
};

TEST(ColorGraphTest, Total) {
    setlocale(LC_ALL, "ko_KR.UTF-8");
    FLexer *lexer = NULL;
    FParser *parser = NULL;
    FBaseNode *node = NULL;
    auto visiter = ColorGraphVisiter();

    {
        // a = 10 + 9 + 8 + 7
        u16 *src = U16(R"(
b = (1 + 10) / (3 - 4) - 1 * 6
)");
        EXPECT_NO_THROW(lexer = CreateLexer(src));
        EXPECT_NO_THROW(parser = CreateParser(lexer));
        EXPECT_NO_THROW(node = Parse(parser));

        EXPECT_FALSE(visiter.visit(node));

        EXPECT_NO_THROW(FreeNode(node));
        EXPECT_NO_THROW(FreeParser(parser));
        EXPECT_NO_THROW(FreeLexer(lexer));
    }
}
