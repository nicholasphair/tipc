#ifndef TIPC_UNIONFINDSOLVER_HPP
#define TIPC_UNIONFINDSOLVER_HPP
#include "term.hpp"
#include "var.hpp"
#include <string>
#include <map>
#include <vector>
#include "../types/TypeConstraint.h"
#include "UnionFind.h"
#include <iostream>

class UnionFindSolver {
public:
    UnionFindSolver() = delete;
    UnionFindSolver(std::vector<TypeConstraint> constrs): constraints(std::move(constrs)) {
        std::vector<Term *> terms;
        for(TypeConstraint t : constraints) {
            terms.push_back(t.lhs);
            terms.push_back(t.rhs);
        }
        unionFind = new UnionFind(terms);
    };
    ~UnionFindSolver();

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


#endif //TIPC_UNIONFINDSOLVER_HPP
