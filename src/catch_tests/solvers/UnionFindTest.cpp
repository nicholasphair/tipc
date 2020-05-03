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
    TestTerm t1;
    TestTerm t2;
    TestTerm t3;
    TestTerm t4;
    std::vector<Term *> seed {&t1, &t2, &t3, &t4};

    UnionFind unionFind(seed);
    REQUIRE(unionFind.find(&t1) == &t1);
    REQUIRE(unionFind.find(&t2) == &t2);
    REQUIRE(unionFind.find(&t3) == &t3);
    REQUIRE(unionFind.find(&t4) == &t4);
}

TEST_CASE("test find 2", "[UnionFind]") {
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
    std::vector<Term *> seed {&t1, &t2};

    UnionFind unionFind(seed);
    REQUIRE_FALSE(unionFind.connected(&t1, &t2));
    unionFind.quick_union(&t1, &t2);
    REQUIRE(unionFind.connected(&t1, &t2));
}

TEST_CASE("test union 2", "[UnionFind]") {
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

TEST_CASE("test union3" , "[UnionFind]") {
    TestTerm t1;
    TestTerm t2;
    TestTerm t3;
    TestTerm t4;
    std::vector<Term *> seed {&t1, &t2, &t3, &t4};

    UnionFind unionFind(seed);
    unionFind.quick_union(&t1, &t3);
    REQUIRE_FALSE(unionFind.find(&t1) == &t1);
    REQUIRE(unionFind.find(&t1) == &t3);
    REQUIRE(unionFind.find(&t3) == &t3);
}

TEST_CASE("test connected" , "[UnionFind]") {
    TestTerm t1;
    TestTerm t2;
    TestTerm t3;
    TestTerm t4;
    std::vector<Term *> seed {&t1, &t2, &t3, &t4};

    UnionFind unionFind(seed);
    unionFind.quick_union(&t1, &t3);
    REQUIRE(unionFind.connected(&t1, &t3));
    REQUIRE_FALSE(unionFind.connected(&t2, &t3));
}

TEST_CASE("test multiple trees" , "[UnionFind]") {
    TestTerm t1;
    TestTerm t2;
    TestTerm t3;
    TestTerm t4;
    TestTerm t5;
    std::vector<Term *> seed {&t1, &t2, &t3, &t4, &t5};
    UnionFind unionFind(seed);

    unionFind.quick_union(&t1, &t2);
    unionFind.quick_union(&t3, &t4);

    REQUIRE(unionFind.connected(&t1, &t2));
    REQUIRE(unionFind.connected(&t3, &t4));
    REQUIRE_FALSE(unionFind.connected(&t1, &t3));
    REQUIRE_FALSE(unionFind.connected(&t2, &t4));
    REQUIRE(unionFind.find(&t5) == &t5);
}
