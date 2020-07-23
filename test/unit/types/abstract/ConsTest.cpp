#include "catch.hpp"
#include "MockTerms.h"

TEST_CASE("test arity is the size of arguments", "[cons]") {
    TestCons cons;
    REQUIRE(0 == cons.arity());

    std::shared_ptr t1 = std::make_shared<TestTerm>();
    std::shared_ptr t2 = std::make_shared<TestTerm>();
    cons.arguments.push_back(t1);
    cons.arguments.push_back(t2);
    REQUIRE(2 == cons.arity());
}

TEST_CASE("test doMatch with same arity and same class", "[cons]") {
    std::shared_ptr<TestCons> cons = std::make_shared<TestCons>();
    std::shared_ptr<TestCons> cons2 = std::make_shared<TestCons>();
    REQUIRE(cons->do_match(cons2));
}

TEST_CASE("test doMatch with different arity and same class", "[cons]") {
    std::shared_ptr<TestCons> cons = std::make_shared<TestCons>();
    std::shared_ptr<TestCons> cons2 = std::make_shared<TestCons>();
    std::shared_ptr<TestTerm> t1 = std::make_shared<TestTerm>();
    cons2->arguments.push_back(t1);
    REQUIRE(!cons->do_match(cons2));
}

TEST_CASE("test doMatch with same arity and different class", "[cons]") {
    std::shared_ptr<TestCons> cons = std::make_shared<TestCons>();
    std::shared_ptr<TestTerm> t1 = std::make_shared<TestTerm>();
    REQUIRE(!cons->do_match(t1));
}

