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

TEST_CASE("test free values", "[.][cons]") {
    // Two free vars from cons.
    std::shared_ptr<TestCons> cons = std::make_shared<TestCons>();
    std::shared_ptr<TestVar> fv1 = std::make_shared<TestVar>();
    std::shared_ptr<TestVar> fv2 = std::make_shared<TestVar>();
    cons->arguments.push_back(fv1);
    cons->arguments.push_back(fv2);

    // Two free vars from arg1.
    std::shared_ptr<TestCons> arg1 = std::make_shared<TestCons>();
    std::shared_ptr<TestVar> fv3 = std::make_shared<TestVar>();
    std::shared_ptr<TestVar> fv4 = std::make_shared<TestVar>();
    arg1->arguments.push_back(fv3);
    arg1->arguments.push_back(fv4);

    // Two free vars from arg2 but one is a duplicate.
    std::shared_ptr<TestCons> arg2 = std::make_shared<TestCons>();
    std::shared_ptr<TestVar> fv5 = std::make_shared<TestVar>();
    std::shared_ptr<TestVar> fv6 = std::make_shared<TestVar>();
    arg1->arguments.push_back(fv5);
    arg1->arguments.push_back(fv6);

    cons->arguments.push_back(arg1);
    cons->arguments.push_back(arg2);
    REQUIRE(5 == cons->free_variables().size());
}
