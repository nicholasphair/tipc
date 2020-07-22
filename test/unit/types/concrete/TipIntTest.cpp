#include "catch.hpp"
#include "TipInt.h"
#include "TipVar.h"
#include "TipMu.h"

TEST_CASE("TipInt: test TipInt is a Cons" "[tip_int]") {
    TipInt t;
    REQUIRE_FALSE(nullptr == dynamic_cast<Cons *>(&t));
}

TEST_CASE("TipInt: test TipInt is a TipType" "[tip_int]") {
    TipInt t;
    REQUIRE_FALSE(nullptr == dynamic_cast<TipType *>(&t));
}

TEST_CASE("TipInt: test TipInt is not a Var or Mu" "[tip_int]") {
    TipInt t;
    REQUIRE(nullptr == dynamic_cast<Var *>(&t));
    REQUIRE(nullptr == dynamic_cast<Mu *>(&t));
}

// TODO
TEST_CASE("TipInt: test substitute returns this", "[.][tip_int]") {
    //TipInt t;

    //AST::NumberExpr n(42);
    //TipVar var(&n);

    //AST::NumberExpr n2(99);
    //TipVar term(&n2);

    //Term * upcast = dynamic_cast<Term *>(&t);
    //REQUIRE(upcast == t.substitute(&var, &term));

    //TipInt t2;
    //Term * upcast2 = dynamic_cast<Term *>(&t2);
    //REQUIRE(upcast2 != t.substitute(&var, &term));
}

TEST_CASE("TipInt: test args is empty", "[tip_int]") {
    TipInt t;
    REQUIRE(t.arguments.empty());
}

TEST_CASE("TipInt: test toString returns int", "[tip_int]") {
    TipInt t;
    REQUIRE("int" == t.toString());
}

TEST_CASE("TipInt: test all TipInts are equal", "[tip_int]") {
    TipInt t1;
    TipInt t2;
    REQUIRE(t1 == t2);
}
