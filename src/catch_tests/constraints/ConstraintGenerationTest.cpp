#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ASTHelper.hpp"
#include "DeclarationsVisitor.hpp"
#include "TIPtreeTypeConstraintVisitor.h"
#include "UnificationError.hpp"
#include <iostream>

TEST_CASE("test constraint generation", "[foo]") {
    std::stringstream stream;
    stream << R"(
      short() {
        var x, y, z;
        x = input;
        y = alloc x;
        *y = x;
        z = *y;
        return z;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    DeclarationsVisitor declarationsVisitor;
    ast->accept(&declarationsVisitor);

    TIPtreeTypeConstraintVisitor typeConstraintVisitor(declarationsVisitor.get_canonicals());
    ast->accept(&typeConstraintVisitor);
    for(auto tc : typeConstraintVisitor.get_constraints()) {
        std::cout << tc.toString() << std::endl;
    }
    REQUIRE(true);
}

