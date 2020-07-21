#include "Cons.h"
#include "UnificationError.h"
#include "Unifier.h"
#include <iostream>
#include <sstream>
#include <vector>

Unifier::Unifier(std::vector<TypeConstraint> constrs) : constraints(std::move(constrs)) {
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

    unionFind = new UnionFind(unique)
}

void Unifier::solve() {
    for(TypeConstraint constraint: constraints) {
        unify(constraint.lhs, constraint.rhs);
    }
}

void Unifier::unify(Term *term1, Term *term2) {
    std::cout << "unifying " << term1->toString() << " and " << term2->toString() << std::endl;
    auto rep1 = unionFind->find(term1);
    auto rep2 = unionFind->find(term2);

    if(rep1 == rep2) {
       return;
    }

    if(isTermVar(rep1) && isTermVar(rep2)) {
        unionFind->quick_union(rep1, rep2);
    } else if(isTermVar(rep1) && isProperType(rep2)) {
        unionFind->quick_union(rep1, rep2);
    } else if(isProperType(rep1) && isTermVar(rep2)) {
        unionFind->quick_union(rep2, rep1);
    } else if(isCons(rep1) && isCons(rep2)) {
        auto f1 = dynamic_cast<Cons *>(rep1);
        auto f2 = dynamic_cast<Cons *>(rep2);
        if(!f1->do_match(f2)) {
            throwUnifyException(f1, f2);
        }

        unionFind->quick_union(rep1, rep2);
        for(int i = 0; i < f1->arguments.size(); i++) {
            auto a1 = f1->arguments.at(i);
            auto a2 = f2->arguments.at(i);
            unify(a1, a2);
        }
    } else {
        throwUnifyException(term1, term2);
    }
}

void Unifier::throwUnifyException(Term * term1, Term * term2) {
    std::stringstream s;
    s << "Cannot unify " << term1->toString() << "and " << term2->toString() <<
        "(respective roots are: " << unionFind->find(term1)->toString() << " and " <<
        unionFind->find(term2)->toString() << ")";
    throw UnificationError(s.str().c_str());
}

bool Unifier::isTermVar(Term * term) {
     return dynamic_cast<Var *>(term) != nullptr;
}

bool Unifier::isProperType(Term * term) {
    return dynamic_cast<Var *>(term) == nullptr;
}

bool Unifier::isCons(Term * term) {
    return dynamic_cast<Cons *>(term) != nullptr;
}
