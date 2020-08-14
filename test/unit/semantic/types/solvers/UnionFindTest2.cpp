#include "catch.hpp"
#include "ASTNumberExpr.h"
#include "TipVar.h"
#include <memory>
#include <utility>
#include <vector>
#include <UnionFind2.h>


static std::vector<std::shared_ptr<TipType>> intsToTipVars(std::vector<int> &values) {
    std::vector<std::shared_ptr<TipType>> pointers;
    for(auto &value : values) {
        ASTNumberExpr * n = new ASTNumberExpr(value);
        pointers.emplace_back(std::make_shared<TipVar>(n));
    }
    return pointers;
}

static void cleanup(std::vector<std::shared_ptr<TipType>> &values) {
    for(auto &value : values) {
        auto tipVar = std::dynamic_pointer_cast<TipVar>(value);
        delete tipVar->node;
    }
}

TEST_CASE("UnionFind2: Test Constructor", "[UnionFind]") {
    std::vector<int> ints {3, 4, 5, 6, 7, 8, 9};
    auto tipVars = std::move(intsToTipVars(ints));
    UnionFind2 unionFind2(tipVars);
    REQUIRE(true);

    cleanup(tipVars);
}

TEST_CASE("UnionFind2: Test find", "[UnionFind]") {
    std::vector<int> ints {3, 4, 5, 6, 7, 8, 9};
    auto tipVars = std::move(intsToTipVars(ints));

    auto three = tipVars.at(0);
    auto four = tipVars.at(1);
    auto five = tipVars.at(2);
    auto six = tipVars.at(3);
    auto seven = tipVars.at(4);
    auto eight = tipVars.at(5);
    auto nine = tipVars.at(6);

    UnionFind2 unionFind2(tipVars);
    unionFind2.quick_union(four, three);
    unionFind2.quick_union(three, eight);
    unionFind2.quick_union(nine, four);

    auto actualRootOfFour = std::dynamic_pointer_cast<TipVar>(unionFind2.find(four));
    auto actualIntOfRootOfFour = dynamic_cast<ASTNumberExpr *>(actualRootOfFour->node)->getValue();
    auto actualRootOfNine = std::dynamic_pointer_cast<TipVar>(unionFind2.find(nine));
    auto actualIntOfRootOfNine = dynamic_cast<ASTNumberExpr *>(actualRootOfNine->node)->getValue();

    REQUIRE(8 == actualIntOfRootOfFour);
    REQUIRE(8 == actualIntOfRootOfNine);
    cleanup(tipVars);
}

TEST_CASE("UnionFind2: Test connected", "[UnionFind]") {
    std::vector<int> ints {3, 4, 5, 6, 7, 8, 9};
    auto tipVars = std::move(intsToTipVars(ints));

    auto three = tipVars.at(0);
    auto four = tipVars.at(1);
    auto five = tipVars.at(2);
    auto six = tipVars.at(3);
    auto seven = tipVars.at(4);
    auto eight = tipVars.at(5);
    auto nine = tipVars.at(6);

    UnionFind2 unionFind2(tipVars);
    unionFind2.quick_union(four, three);
    unionFind2.quick_union(three, eight);
    unionFind2.quick_union(nine, four);

    REQUIRE(unionFind2.connected(three, nine));
    REQUIRE_FALSE(unionFind2.connected(five, six));
    cleanup(tipVars);
}