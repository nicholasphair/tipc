#include "catch.hpp"
#include <TipInt.hpp>
#include <TipRef.hpp>

TEST_CASE("TipRef: test TipRefs are compared by their underlying term" "[TipRef]") {
    TipInt term;
    TipRef ref(&term);
    TipRef ref2(&term);

    REQUIRE(ref == ref2);
}

