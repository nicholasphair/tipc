#include "ASTHelper.h"
#include "SymbolTable.h"
#include "TypeConstraintVisitor.h"
#include "catch.hpp"
#include <iostream>
#include <PrettyPrinter.h>
#include <types/concrete/TipInt.h>
#include <types/concrete/TipRef.h>
#include <types/concrete/TipAlpha.h>
#include <types/concrete/TipFunction.h>
#include "FriendlyNodeStringifier.h"

static void printConstraints(const std::vector<TypeConstraint> constraints) {
    for(auto &tc : constraints) {
        std::cout << FriendlyNodeStringifier::stringify(tc.lhs.get())
                  << " = "
                  << FriendlyNodeStringifier::stringify(tc.rhs.get())
                  << std::endl;
    }
}


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

    std::stringstream outputStream;
    auto symbols = SymbolTable::build(ast.get(), outputStream);


    TypeConstraintVisitor typeConstraintVisitor(*symbols.value().get());
    ast->accept(&typeConstraintVisitor);

    auto tcs = typeConstraintVisitor.get_constraints();
    printConstraints(tcs);

    // TODO: Make expected constraints and compare that way.
    REQUIRE(*(tcs.at(0).lhs) == *(tcs.at(1).rhs));
    REQUIRE(*(tcs.at(2).lhs) == *(tcs.at(3).rhs));
    //REQUIRE(*(tcs.at(2).lhs) == *(tcs.at(4).lhs));
    //REQUIRE(*(tcs.at(3).rhs) == *(tcs.at(4).rhs));
    //REQUIRE(*(tcs.at(4).lhs) == *(tcs.at(6).lhs));

    // 9 is right...
    //REQUIRE(tcs.size() == 8);
}

/*
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
*/
