#pragma once

#include "Term.h"
#include "Var.h"
#include "Cons.h"
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
    void unify(std::shared_ptr<Term> t1, std::shared_ptr<Term> t2);
private:
    bool isTermVar(std::shared_ptr<Term>);
    bool isProperType(std::shared_ptr<Term>);
    bool isCons(std::shared_ptr<Term>);
    void throwUnifyException(std::shared_ptr<Term> term1, std::shared_ptr<Term> term2);
    std::vector<TypeConstraint> constraints;
    std::shared_ptr<UnionFind<std::shared_ptr<Term>>> unionFind;
};

