#include "catch.hpp"
#include "TipInt.hpp"
#include "TipVar.hpp"
#include "TipMu.hpp"

TEST_CASE("TipVar: test TipVars objects with the same underlying node are equal" "[TipVar]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    TipVar var2(&n);
    REQUIRE(var == var2);
}

TEST_CASE("TipVar: test TipVars objects with different underlying node are not equal" "[TipVar]") {
    TIPtree::NumberExpr n(99);
    TIPtree::NumberExpr n1(99);
    TipVar var(&n);
    TipVar var2(&n1);
    REQUIRE_FALSE(var == var2);
}

TEST_CASE("TipVar: test me" "[TipVar]") {
 //COMPARE WITH TWO VAREXPRS!!! TODO
    std::string name("foo");
    TIPtree::VariableExpr vexpr(name);
    TIPtree::VariableExpr vexpr2(name);
    TipVar var(&vexpr);
    TipVar var2(&vexpr2);

    REQUIRE(var == var2);
}

TEST_CASE("TipVar: test TipVar is a Var" "[TipVar]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE_FALSE(nullptr == dynamic_cast<Var *>(&var));
}

TEST_CASE("TipVar: test TipVar is a TipType" "[TipVar]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE_FALSE(nullptr == dynamic_cast<TipType *>(&var));
}

TEST_CASE("TipVar: test TipVar is not a Cons or Mu" "[TipVar]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE(nullptr == dynamic_cast<Cons *>(&var));
    REQUIRE(nullptr == dynamic_cast<Mu *>(&var));
}

TEST_CASE("TipVar: test free_variables" "[TipVar]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE(1 == var.free_variables().size());
}

TEST_CASE("TipVar: test toString returns alpha + val", "[TipVar]") {
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    REQUIRE("α<42>" == var.toString());
}
