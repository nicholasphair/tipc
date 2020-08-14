#include "catch.hpp"
#include "ASTHelper.h"
#include "ASTVariableExpr.h"
#include "Stringifier.h"
#include "TipFunction.h"
#include "TipInt.h"
#include "TypeConstraintCollectVisitor.h"
#include "TypeConstraintUnifyVisitor.h"
#include "TypeConstraintVisitor.h"
#include "UnificationError.h"
#include "Unifier.h"
#include <iostream>
#include <Unifier2.h>

TEST_CASE("Unifier: Collect and then unify constraints", "[Unifier, Collect]") {

    SECTION("Test type-safe program 1") {
        std::stringstream program;
        program << R"(
            short() {
              var x, y, z;
              x = input;
              y = alloc x;
              *y = x;
              z = *y;
              return z;
            }
         )";

        auto ast = ASTHelper::build_ast(program);
        auto symbols = SymbolTable::build(ast.get());

        TypeConstraintCollectVisitor visitor(symbols.get());
        ast->accept(&visitor);

        Unifier unifier(visitor.getCollectedConstraints());
        REQUIRE_NOTHROW(unifier.solve());
    }

    SECTION("Test unification error 1") {
        std::stringstream program;
        program << R"(
            bar(g,x) {
                var r;
                if (x==0){
                    r=g;
                } else {
                    r=bar(2,0);
                }
                return r+1;
            }

            main() {
                return bar(null,1);
            }
        )";

        auto ast = ASTHelper::build_ast(program);
        auto symbols = SymbolTable::build(ast.get());

        TypeConstraintCollectVisitor visitor(symbols.get());
        ast->accept(&visitor);

        Unifier2 unifier(visitor.getCollectedConstraints());
        REQUIRE_THROWS_AS(unifier.solve(), UnificationError);
    }

    SECTION("Test unification error 2") {
        std::stringstream program;
        program << R"(
            foo(p) {
                return *p;
            }

            main() {
                var x;
                x = 5;
                x = foo;
                return 4;
            }
        )";

        auto ast = ASTHelper::build_ast(program);
        auto symbols = SymbolTable::build(ast.get());

        TypeConstraintCollectVisitor visitor(symbols.get());
        ast->accept(&visitor);

        Unifier unifier(visitor.getCollectedConstraints());
        REQUIRE_THROWS_AS(unifier.solve(), UnificationError);
    }

    SECTION("Test unification error 3") {
        std::stringstream program;
        program << R"(
            main() {
                var x, y;
                x = 5;
                y = 10;
                x = &y;
                return 4;
            }
        )";

        auto ast = ASTHelper::build_ast(program);
        auto symbols = SymbolTable::build(ast.get());

        TypeConstraintCollectVisitor visitor(symbols.get());
        ast->accept(&visitor);

        Unifier unifier(visitor.getCollectedConstraints());
        REQUIRE_THROWS_AS(unifier.solve(), UnificationError);
    }

}

TEST_CASE("Unifier: Unify constraints on the fly", "[Unifier, On-the-fly]") {
    /*
    SECTION("Test type-safe program 1") {
        std::stringstream program;
        program << R"(
            short() {
              var x, y, z;
              x = input;
              y = alloc x;
              *y = x;
              z = *y;
              return z;
            }
         )";

        auto ast = ASTHelper::build_ast(program);
        auto symbols = SymbolTable::build(ast.get());

        TypeConstraintUnifyVisitor visitor(symbols.get());
        REQUIRE_NOTHROW(ast->accept(&visitor));
    }
     */

    SECTION("Test unification error 1") {
        std::stringstream program;
        program << R"(
            bar(g,x) {
                var r;
                if (x==0){
                    r=g;
                } else {
                    r=bar(2,0);
                }
                return r+1;
            }

            main() {
                return bar(null,1);
            }
        )";

        auto ast = ASTHelper::build_ast(program);
        auto symbols = SymbolTable::build(ast.get());

        TypeConstraintUnifyVisitor visitor(symbols.get());
        REQUIRE_THROWS_AS(ast->accept(&visitor), UnificationError);
    }

    /*
    SECTION("Test unification error 2") {
        std::stringstream program;
        program << R"(
            foo(p) {
                return *p;
            }

            main() {
                var x;
                x = 5;
                x = foo;
                return 4;
            }
        )";

        auto ast = ASTHelper::build_ast(program);
        auto symbols = SymbolTable::build(ast.get());

        TypeConstraintUnifyVisitor visitor(symbols.get());
        REQUIRE_THROWS_AS(ast->accept(&visitor), UnificationError);
    }

    SECTION("Test unification error 3") {
        std::stringstream program;
        program << R"(
            main() {
                var x, y;
                x = 5;
                y = 10;
                x = &y;
                return 4;
            }
        )";

        auto ast = ASTHelper::build_ast(program);
        auto symbols = SymbolTable::build(ast.get());

        TypeConstraintUnifyVisitor visitor(symbols.get());
        REQUIRE_THROWS_AS(ast->accept(&visitor), UnificationError);
    }
     */

}


TEST_CASE("Unifier: Test unifying TipCons with different arities", "[Unifier]") {
    std::vector<std::shared_ptr<TipType>> paramsA {std::make_shared<TipInt>()};
    auto retA = std::make_shared<TipInt>();
    auto tipFunctionA = std::make_shared<TipFunction>(paramsA, retA);

    std::vector<std::shared_ptr<TipType>> paramsB {std::make_shared<TipInt>(), std::make_shared<TipInt>()};
    auto retB = std::make_shared<TipInt>();
    auto tipFunctionB = std::make_shared<TipFunction>(paramsB, retB);

    TypeConstraint constraint(tipFunctionA, tipFunctionB);
    std::vector<TypeConstraint> constraints {constraint};

    Unifier unifier(constraints);
    REQUIRE_THROWS_AS(unifier.unify(tipFunctionA.get(), tipFunctionB.get()), UnificationError);
}

TEST_CASE("Unifier: Test unifying TipCons with the same arity", "[Unifier]") {
    std::vector<std::shared_ptr<TipType>> params {std::make_shared<TipInt>()};
    auto ret = std::make_shared<TipInt>();
    auto tipFunctionA = std::make_shared<TipFunction>(params, ret);

    auto tipFunctionB = std::make_shared<TipFunction>(params, ret);

    TypeConstraint constraint(tipFunctionA, tipFunctionB);
    std::vector<TypeConstraint> constraints {constraint};

    Unifier unifier(constraints);
    REQUIRE_NOTHROW(unifier.unify(tipFunctionA.get(), tipFunctionB.get()));
}


TEST_CASE("Unifier: Test unifying proper types with a type variable", "[Unifier]") {
    ASTVariableExpr variableExpr("foo");
    auto tipVar = std::make_shared<TipVar>(&variableExpr);
    auto tipInt = std::make_shared<TipInt>();

    TypeConstraint constraint(tipVar, tipInt);
    std::vector<TypeConstraint> constraints {constraint};

    Unifier unifier(constraints);
    REQUIRE_NOTHROW(unifier.unify(tipVar.get(), tipInt.get()));
}

TEST_CASE("Unifier: Test unifying two different type variables", "[Unifier]") {
    ASTVariableExpr variableExprA("foo");
    auto tipVarA = std::make_shared<TipVar>(&variableExprA);

    ASTVariableExpr variableExprB("foo");
    auto tipVarB = std::make_shared<TipVar>(&variableExprB);

    TypeConstraint constraint(tipVarA, tipVarB);
    std::vector<TypeConstraint> constraints {constraint};

    Unifier unifier(constraints);
    REQUIRE_NOTHROW(unifier.unify(tipVarA.get(), tipVarB.get()));
}
