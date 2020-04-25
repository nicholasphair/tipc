#include "catch.hpp"
#include "tip_int.hpp"
#include "tip_var.hpp"
#include "tip_mu.hpp"

TEST_CASE("TipVar: test TipVars can be instantiated", "[tip_var]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE(var.is_concrete());
}

TEST_CASE("TipVar: test TipVar is a Var" "[tip_var]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE_FALSE(nullptr == dynamic_cast<Var *>(&var));
}

TEST_CASE("TipVar: test TipVar is a TipType" "[tip_var]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE_FALSE(nullptr == dynamic_cast<TipType *>(&var));
}

TEST_CASE("TipVar: test TipVar is not a Cons or Mu" "[tip_var]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE(nullptr == dynamic_cast<Cons *>(&var));
    REQUIRE(nullptr == dynamic_cast<Mu *>(&var));
}

TEST_CASE("TipVar: test free_variables" "[tip_var]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE(1 == var.free_variables().size());
}

TEST_CASE("TipVar: test toString returns alpha + val", "[tip_var]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE("α<42>" == var.toString());
}
