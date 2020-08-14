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
#include <vector>

class Unifier {
public:
    Unifier();
    explicit Unifier(std::vector<TypeConstraint>);
    ~Unifier() = default;
    Unifier(const Unifier& other) = delete;
    Unifier(Unifier&& other) noexcept = default;
    Unifier& operator=(const Unifier& other) = delete;
    Unifier& operator=(Unifier&& other) noexcept = default;

    void solve();
    void unify(TipType const * t1, TipType const * t2);
private:
    std::vector<TipType *> deduplicate(std::vector<TipType *> types);
    static bool isTypeVariable(TipType const * TipType);
    static bool isProperType(TipType const *);
    static bool isCons(TipType const *);
    void throwUnifyException(TipType const * TipType1, TipType const * TipType2);
    std::vector<TypeConstraint> constraints;
    std::unique_ptr<UnionFind<TipType>> unionFind;
};

