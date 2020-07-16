#include "catch.hpp"
#include "MockTerms.h"

TEST_CASE("test arity is the size of arguments", "[cons]") {
    TestCons cons;
    REQUIRE(0 == cons.arity());

    TestTerm t1;
    TestTerm t2;
    cons.arguments.push_back(&t1);
    cons.arguments.push_back(&t2);
    REQUIRE(2 == cons.arity());
}

TEST_CASE("test doMatch with same arity and same class", "[cons]") {
    TestCons cons;
    TestCons cons2;
    REQUIRE(cons.do_match(&cons2));
}

TEST_CASE("test doMatch with different arity and same class", "[cons]") {
    TestCons cons;
    TestCons cons2;
    TestTerm term;
    cons2.arguments.push_back(&term);
    REQUIRE(!cons.do_match(&cons2));
}

TEST_CASE("test doMatch with same arity and different class", "[cons]") {
    TestCons cons;
    TestVar term;
    REQUIRE(!cons.do_match(&term));
}

TEST_CASE("test free values", "[cons]") {
    // Two free vars from cons.
    TestCons cons;
    TestVar fv1;
    TestVar fv2;
    cons.arguments.push_back(&fv1);
    cons.arguments.push_back(&fv2);

    // Two free vars from arg1.
    TestCons arg1;
    TestVar fv3;
    TestVar fv4;
    arg1.arguments.push_back(&fv3);
    arg1.arguments.push_back(&fv4);

    // Two free vars from arg2 but one is a duplicate.
    TestCons arg2;
    TestVar fv5;
    TestVar fv6 = fv5;
    arg1.arguments.push_back(&fv5);
    arg1.arguments.push_back(&fv6);

    cons.arguments.push_back(&arg1);
    cons.arguments.push_back(&arg2);
    REQUIRE(5 == cons.free_variables().size());
}
