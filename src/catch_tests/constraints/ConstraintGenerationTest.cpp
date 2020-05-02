#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ASTHelper.hpp"
#include "DeclarationsVisitor.hpp"
#include "TIPtreeTypeConstraintVisitor.h"
#include "UnificationError.hpp"
#include <iostream>

TEST_CASE("test constraint generation", "[TIPtreeTypeConstraintVisitor]") {
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
    auto tcs = typeConstraintVisitor.get_constraints();
    for(auto tc : tcs) {
        std::cout << tc << std::endl;
    }
    REQUIRE(tcs.size() == 8);
}

TEST_CASE("test constraint generation 2", "[TIPtreeTypeConstraintVisitor]") {
    std::stringstream stream;
    stream << R"(
      foo() {
        var x, y, z;
        x = 5;
        y = &y;
        z = foo;
        return z;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    DeclarationsVisitor declarationsVisitor;
    ast->accept(&declarationsVisitor);

    TIPtreeTypeConstraintVisitor typeConstraintVisitor(declarationsVisitor.get_canonicals());
    ast->accept(&typeConstraintVisitor);
    auto tcs = typeConstraintVisitor.get_constraints();
    for(auto tc : tcs) {
        std::cout << tc << std::endl;
    }

    REQUIRE(tcs.size() == 6);
}
