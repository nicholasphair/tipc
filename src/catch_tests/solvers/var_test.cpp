#include "catch.hpp"
#include "mock_terms.h"

TEST_CASE("test the free variables of a var includes itself", "[var]") {
    TestVar var;
    REQUIRE(1 == var.free_variables().size());
    REQUIRE(1 == var.free_variables().count(&var));

    TestVar var2;
    REQUIRE(0 == var.free_variables().count(&var2));
}

TEST_CASE("test substitute", "[var]") {
    TestVar var;
    TestVar var2;
    TestVar var3;

    REQUIRE(&var2 == var.substitute(&var, &var2));
    REQUIRE(&var == var.substitute(&var2, &var));
    REQUIRE(&var == var.substitute(&var2, &var3));
}
