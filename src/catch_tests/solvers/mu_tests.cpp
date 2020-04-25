#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MockTerms.h"

TEST_CASE("test free variables returns ts free vars minus v", "[mu]") {
    TestMu mu;

    TestCons cons;
    TestVar fv1;
    TestVar fv2;
    TestVar fv3;
    cons.arguments.push_back(&fv1);
    cons.arguments.push_back(&fv2);
    cons.arguments.push_back(&fv3);

    mu.t = &cons;

    REQUIRE(3 == mu.free_variables().size());

    mu.v = &fv3;
    REQUIRE(2 == mu.free_variables().size());
    REQUIRE(1 == mu.free_variables().count(&fv1));
    REQUIRE(1 == mu.free_variables().count(&fv2));
    REQUIRE(0 == mu.free_variables().count(&fv3));
}


