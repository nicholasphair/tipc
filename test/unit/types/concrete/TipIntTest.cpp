#include "catch.hpp"
#include "TipInt.h"
#include "TipVar.h"

TEST_CASE("TipInt: test TipInt is a Cons" "[tip_int]") {
    TipInt t;
    REQUIRE_FALSE(nullptr == dynamic_cast<Cons *>(&t));
}

TEST_CASE("TipInt: test TipInt is a TipType" "[tip_int]") {
    TipInt t;
    REQUIRE_FALSE(nullptr == dynamic_cast<TipType *>(&t));
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
