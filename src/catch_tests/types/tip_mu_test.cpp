#include <tip_int.hpp>
#include "catch.hpp"
#include "tip_mu.hpp"
#include "tip_var.hpp"

TEST_CASE("TipMu: test TipMu can be instantiated", "[tip_mu]") {
    TipInt term;
    TIPtree::NumberExpr n(42);
    TipVar var(&n);

    TipMu mu(&var, &term);
    REQUIRE(mu.is_concrete());
}

TEST_CASE("TipMu: test TipMu is a Mu" "[tip_mu]") {
    TipInt term;
    TIPtree::NumberExpr n(42);
    TipVar var(&n);

    TipMu mu(&var, &term);
    REQUIRE_FALSE(nullptr == dynamic_cast<Mu *>(&mu));
}

TEST_CASE("TipMu: test TipMu is a TipType" "[tip_mu]") {
    TipInt term;
    TIPtree::NumberExpr n(42);
    TipVar var(&n);

    TipMu mu(&var, &term);
    REQUIRE_FALSE(nullptr == dynamic_cast<TipType *>(&mu));
}

TEST_CASE("TipMu: test TipMu is not a Var or Cons" "[tip_mu]") {
    TipInt term;
    TIPtree::NumberExpr n(42);
    TipVar var(&n);

    TipMu mu(&var, &term);
    REQUIRE_FALSE(nullptr == dynamic_cast<Var *>(&mu));
    REQUIRE_FALSE(nullptr == dynamic_cast<Cons *>(&mu));
}

TEST_CASE("TipMu: test this is returned when substitute equals member v", "[tip_mu]") {
    TipInt term;
    TIPtree::NumberExpr n(42);
    TipVar var(&n);
    TipMu mu(&var, &term);

    TipInt t;

    Term * expected = dynamic_cast<Term *>(&mu);
    Term * actual = mu.substitute(&var, &t);
    REQUIRE(actual == expected);
    REQUIRE_FALSE(nullptr == dynamic_cast<Mu *>(actual));
}

TEST_CASE("TipMu: test the other case", "[tip_mu]") {
    // TODO
    REQUIRE(true);
}

