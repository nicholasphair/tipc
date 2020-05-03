#ifndef TIPC_UNIONFINDSOLVER_HPP
#define TIPC_UNIONFINDSOLVER_HPP
#include "Term.hpp"
#include "Var.hpp"
#include "Cons.hpp"
#include <string>
#include <map>
#include <vector>
#include "../constraints/TypeConstraint.h"
#include "UnionFind.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>

class UnionFindSolver {
public:
    UnionFindSolver() = delete;
    UnionFindSolver(std::vector<TypeConstraint> constrs): constraints(std::move(constrs)) {
        std::vector<Term *> terms;
        for(TypeConstraint t : constraints) {
            auto l = t.lhs;
            auto r = t.rhs;
            terms.push_back(l);
            terms.push_back(r);

            if(auto f1 = dynamic_cast<Cons *>(l)) {
                for(auto a : f1->arguments) terms.push_back(a);
            }
            if(auto f2 = dynamic_cast<Cons *>(r)) {
                for(auto a : f2->arguments) terms.push_back(a);
            }
        }

        // Deduplicate terms.
        std::vector<Term *> unique;
        for(auto t : terms) {
            bool add = true;
            for(auto u : unique) {
                if(*t == *u) add = false;
            }
            if(add) unique.push_back(std::move(t));
        }

        unionFind = new UnionFind(unique);
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
