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
    void unify(Term * t1, Term * t2);
private:
    bool isTermVar(Term *);
    bool isProperType(Term *);
    bool isCons(Term *);
    void throwUnifyException(Term * term1, Term * term2);
    std::vector<TypeConstraint> constraints;
    UnionFind * unionFind;
};

