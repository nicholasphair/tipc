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

    for(auto tc : tcs) {
        std::cout << tc << std::endl;
    }
    UnionFindSolver unionFindSolver(tcs);

    REQUIRE_NOTHROW(unionFindSolver.solve());
}

TEST_CASE("test unification error 1", "[UnionFindSolver]") {
    std::stringstream stream;
    stream << R"(
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

    REQUIRE_THROWS_AS(unionFindSolver.solve(), UnificationError);
}

TEST_CASE("test unification error 2", "[UnionFindSolver]") {
    std::stringstream stream;
    stream << R"(
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

    REQUIRE_THROWS_AS(unionFindSolver.solve(), UnificationError);
}

TEST_CASE("test unification error 3", "[UnionFindSolver]") {
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

    REQUIRE_THROWS_AS(unionFindSolver.solve(), UnificationError);
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
