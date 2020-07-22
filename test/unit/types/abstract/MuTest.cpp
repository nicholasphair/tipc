#include "catch.hpp"
#include "MockTerms.h"

TEST_CASE("test free variables returns ts free vars minus v", "[.][mu]") {
    TestMu mu;

    std::shared_ptr<TestCons> cons = std::make_shared<TestCons>();
    std::shared_ptr<TestVar> fv1 = std::make_shared<TestVar>();
    std::shared_ptr<TestVar> fv2 = std::make_shared<TestVar>();
    std::shared_ptr<TestVar> fv3 = std::make_shared<TestVar>();
    cons->arguments.push_back(fv1);
    cons->arguments.push_back(fv2);
    cons->arguments.push_back(fv3);

    mu.t = cons;

    REQUIRE(3 == mu.free_variables().size());

    mu.v = fv3;
    REQUIRE(2 == mu.free_variables().size());
    REQUIRE(1 == mu.free_variables().count(fv1));
    REQUIRE(1 == mu.free_variables().count(fv2));
    REQUIRE(0 == mu.free_variables().count(fv3));
}


