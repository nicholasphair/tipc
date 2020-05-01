#include "catch.hpp"
#include "mock_terms.h"
#include "UnionFindSolver.hpp"
#include "TypeConstraint.h"
#include "UnificationError.hpp"
#include <iostream>

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
