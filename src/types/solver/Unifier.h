#pragma once

#include "TipType.h"
#include "TipVar.h"
#include "TipCons.h"
#include <string>
#include <map>
#include <vector>
#include "../constraints/TypeConstraint.h"
#include "UnionFind.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>

class Unifier {
public:
    Unifier() = delete;
    Unifier(std::vector<TypeConstraint>);
    ~Unifier();

    void solve();
    void unify(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2);
private:
    bool isTipVar(std::shared_ptr<TipType>);
    bool isProperType(std::shared_ptr<TipType>);
    bool isCons(std::shared_ptr<TipType>);
    void throwUnifyException(std::shared_ptr<TipType> TipType1, std::shared_ptr<TipType> TipType2);
    std::vector<TypeConstraint> constraints;
    std::shared_ptr<UnionFind<std::shared_ptr<TipType>>> unionFind;
};

