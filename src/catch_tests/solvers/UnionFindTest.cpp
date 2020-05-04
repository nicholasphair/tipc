#include <TipVar.hpp>
#include "catch.hpp"
#include "MockTerms.h"
#include "UnionFind.h"

TEST_CASE("test constructor", "[UnionFind]") {
    TestTerm t1;
    TestTerm t2;
    TestTerm t3;
    TestTerm t4;
    std::vector<Term *> seed {&t1, &t2, &t3, &t4};

    UnionFind unionFind(seed);
    REQUIRE(true);
}

TEST_CASE("test find", "[UnionFind]") {
    TIPtree::Identifier id3("3");
    TIPtree::Identifier id4("4");
    TIPtree::Identifier id8("8");

    TipVar var3(&id3);
    TipVar var4(&id4);
    TipVar var8(&id8);
    std::vector<Term *> seed {&var3, &var4, &var8};

    UnionFind unionFind(seed);
    unionFind.print_edges();
    unionFind.quick_union(&var4, &var3);
    unionFind.print_edges();
    unionFind.quick_union(&var4, &var8);
    unionFind.print_edges();
    REQUIRE(unionFind.find(&var4) == &var8);
}

TEST_CASE("test union", "[UnionFind]") {
    TestTerm t1;
    TestTerm t2;
    TestTerm t3;
    TestTerm t4;
    std::vector<Term *> seed {&t1, &t2, &t3, &t4};

    UnionFind unionFind(seed);
    unionFind.quick_union(&t1, &t2);
    unionFind.quick_union(&t2, &t3);
    unionFind.quick_union(&t3, &t4);
    REQUIRE(unionFind.connected(&t4, &t1));
}
