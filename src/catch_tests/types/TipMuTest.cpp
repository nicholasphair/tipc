#include "catch.hpp"
#include <TipInt.hpp>
#include "TipMu.hpp"
#include "TipVar.hpp"

TEST_CASE("TipMu: test TipMus are compared by their underlying t and v" "[TipMu]") {
    TipInt term;
    TIPtree::NumberExpr n(42);
    TipVar var(&n);

    TipMu mu(&var, &term);
    TipMu mu2(&var, &term);
    REQUIRE(mu == mu2);
}

TEST_CASE("TipMu: test not equals" "[TipMu]") {
    TipInt term;
    TIPtree::NumberExpr n(42);
    TIPtree::NumberExpr n2(42);
    TipVar var(&n);
    TipVar var2(&n2);

    TipMu mu(&var, &term);
    TipMu mu2(&var2, &term);
    REQUIRE(mu != mu2);
}

TEST_CASE("TipMu: test TipMu is a Mu" "[TipMu]") {
    TipInt term;
    TIPtree::NumberExpr n(42);
    TipVar var(&n);

    TipMu mu(&var, &term);
    REQUIRE_FALSE(nullptr == dynamic_cast<Mu *>(&mu));
}

TEST_CASE("TipMu: test TipMu is a TipType" "[TipMu]") {
    TipInt term;
    TIPtree::NumberExpr n(42);
    TipVar var(&n);

    TipMu mu(&var, &term);
    REQUIRE_FALSE(nullptr == dynamic_cast<TipType *>(&mu));
}

TEST_CASE("TipMu: test this is returned when substitute equals member v", "[TipMu]") {
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
