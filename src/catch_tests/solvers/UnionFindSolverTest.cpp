#include "catch.hpp"
#include "MockTerms.h"
#include "UnionFindSolver.hpp"
#include "UnificationError.hpp"
#include <iostream>
#include "ASTHelper.hpp"
#include "DeclarationsVisitor.hpp"
#include "TIPtreeTypeConstraintVisitor.h"
#include "TypeConstraint.h"

TEST_CASE("test short", "[UnionFindSolver]") {
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

    UnionFindSolver unionFindSolver(tcs);

    unionFindSolver.solve();
    REQUIRE(true);
}

TEST_CASE("test unification error", "[UnionFindSolver]") {
    std::stringstream stream;
    stream << R"(
        main() {
            var x, y;
            x = 5;
            y = 10;
            x = &y;
            return 4;
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
    std::cout << "\n\n" << std::endl;
    UnionFindSolver unionFindSolver(tcs);

    unionFindSolver.solve();
    REQUIRE(true);
}

TEST_CASE("test unifying cons with different arity", "[UnionFindSolver]") {
    TestNCons oneCons(1);
    TestNCons twoCons(2);
    TypeConstraint constraint(&oneCons, &twoCons);
    std::vector<TypeConstraint> constraints {constraint};

    UnionFindSolver solver(constraints);
    REQUIRE_THROWS_AS(solver.unify(&oneCons, &twoCons), UnificationError);
}

TEST_CASE("test unifying two different proper types", "[UnionFindSolver]") {
    TestTerm t1;
    TestTerm t2;
    TypeConstraint constraint(&t1, &t2);
    std::vector<TypeConstraint> constraints {constraint};

    UnionFindSolver solver(constraints);
    REQUIRE_THROWS_AS(solver.unify(&t1, &t2), UnificationError);
}

TEST_CASE("test unifying proper types and termvar", "[UnionFindSolver]") {
    TestTerm t1;
    TestVar v1;
    TypeConstraint constraint(&t1, &v1);
    std::vector<TypeConstraint> constraints {constraint};

    UnionFindSolver solver(constraints);
    REQUIRE_NOTHROW(solver.unify(&t1, &v1));
}

TEST_CASE("test unifying two different termvars", "[UnionFindSolver]") {
    TestVar t1;
    TestVar t2;
    TypeConstraint constraint(&t1, &t2);
    std::vector<TypeConstraint> constraints {constraint};

    UnionFindSolver solver(constraints);
    REQUIRE_NOTHROW(solver.unify(&t1, &t2));
}

TEST_CASE("test unifying cons with same arity", "[UnionFindSolver]") {
    TestNCons t1(42);
    TestNCons t2(42);
    TypeConstraint constraint(&t1, &t2);
    std::vector<TypeConstraint> constraints {constraint};

    UnionFindSolver solver(constraints);
    REQUIRE_NOTHROW(solver.unify(&t1, &t2));
}
