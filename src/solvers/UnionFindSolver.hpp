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

class UnionFindSolver {
public:
    UnionFindSolver() = delete;
    UnionFindSolver(std::vector<TypeConstraint> constrs): constraints(std::move(constrs)) {
        std::vector<Term *> terms;
        for(TypeConstraint t : constraints) {
            // TODO: SUBTERMS
            terms.push_back(t.lhs);
            terms.push_back(t.rhs);
            //auto l = t.lhs;
            //auto r = t.rhs;

            //// --------------------------------------------------------------------------------
            //// Safe add.
            //// --------------------------------------------------------------------------------
            //bool lexist = false;
            //bool rexist = false;
            //for(auto term : terms) {
            //    if(term->equals(l)) {
            //        lexist = true;
            //    }
            //    if(term->equals(r)) {
            //        rexist = true;
            //    }
            //}

            //if(!lexist) {
            //    terms.push_back(l);
            //}
            //if(!rexist) {
            //    terms.push_back(r);
            //}
            //// --------------------------------------------------------------------------------

            //auto f1 = dynamic_cast<Cons *>(l);
            //auto f2 = dynamic_cast<Cons *>(r);
            //if(f1 != nullptr) {
            //    for(auto a : f1->arguments) {
            //        bool exists = false;
            //        for(auto term : terms) {
            //            if(term->equals(a)) {
            //                exists = true;
            //            }
            //        }
            //        if(!exists) {
            //            terms.push_back(a);
            //        }
            //    }
            //}

            //if(f2 != nullptr) {
            //    for(auto a : f2->arguments) {
            //        bool exists = false;
            //        for(auto term : terms) {
            //            if(term->equals(a)) {
            //                exists = true;
            //            }
            //        }
            //        if(!exists) {
            //            terms.push_back(a);
            //        }
            //    }
            //}
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
