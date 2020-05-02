#include "catch.hpp"
#include "TypeConstraint.h"
#include "MockTerms.h"

TEST_CASE("constraint are compared term-wise", "[TypeConstraint]") {
    TestNCons twoCons(2);

    TypeConstraint constraint(&twoCons, &twoCons);
    TypeConstraint constraint2(&twoCons, &twoCons);
    REQUIRE(constraint == constraint2);
    REQUIRE_FALSE(constraint != constraint2);
}

TEST_CASE("inequality is the negation of equality", "[TypeConstraint]") {
    TestNCons twoCons(2);
    TestNCons threeCons(3);

    TypeConstraint constraint(&twoCons, &twoCons);
    TypeConstraint constraint2(&twoCons, &twoCons);
    REQUIRE(constraint == constraint2);
    REQUIRE_FALSE(constraint != constraint2);
}
