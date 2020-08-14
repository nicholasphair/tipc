#pragma once

#include "TipCons.h"
#include "TipType.h"
#include "TipVar.h"
#include "TypeConstraint.h"
#include "UnionFind.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <unordered_set>
#include "UnionFind2.h"
#include <vector>

class Unifier2 {
public:
    Unifier2();
    explicit Unifier2(std::vector<TypeConstraint>);
    ~Unifier2() = default;

    void solve();
    void unify(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2);
private:
    std::vector<std::shared_ptr<TipType>> deduplicate(std::vector<std::shared_ptr<TipType>> types);
    static bool isTypeVariable(std::shared_ptr<TipType>);
    static bool isProperType(std::shared_ptr<TipType>);
    static bool isCons(std::shared_ptr<TipType>);
    void throwUnifyException(std::shared_ptr<TipType> TipType1, std::shared_ptr<TipType> TipType2);
    std::vector<TypeConstraint> constraints;
    std::unique_ptr<UnionFind2> unionFind;
};

