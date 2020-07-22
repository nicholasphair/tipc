#include "Cons.h"
#include "UnificationError.h"
#include "Unifier.h"
#include <iostream>
#include <sstream>
#include <vector>

// TODO: use dynamic pointer cast.
Unifier::Unifier(std::vector<TypeConstraint> constrs) : constraints(std::move(constrs)) {
    std::vector<std::shared_ptr<Term>> terms;
    for(TypeConstraint t : constraints) {
        auto l = t.lhs;
        auto r = t.rhs;
        terms.push_back(l);
        terms.push_back(r);

        if(auto f1 = dynamic_cast<Cons *>(l.get())) {
            for(auto a : f1->arguments) terms.push_back(a);
        }
        if(auto f2 = dynamic_cast<Cons *>(r.get())) {
            for(auto a : f2->arguments) terms.push_back(a);
        }
    }

    // Deduplicate terms.
    std::vector<std::shared_ptr<Term>> unique;
    for(auto t : terms) {
        bool add = true;
        for(auto u : unique) {
            if(*t == *u) add = false;
        }
        if(add) unique.push_back(t);
    }

    unionFind = std::make_shared<UnionFind<std::shared_ptr<Term>>>(unique);
}

void Unifier::solve() {
    for(TypeConstraint constraint: constraints) {
        unify(constraint.lhs, constraint.rhs);
    }
}

void Unifier::unify(std::shared_ptr<Term> term1, std::shared_ptr<Term> term2) {
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
        auto f1 = std::dynamic_pointer_cast<Cons>(rep1);
        auto f2 = std::dynamic_pointer_cast<Cons>(rep2);
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

Unifier::~Unifier() {

}

void Unifier::throwUnifyException(std::shared_ptr<Term> term1, std::shared_ptr<Term> term2) {
    std::stringstream s;
    s << "Cannot unify " << term1->toString() << "and " << term2->toString() <<
        "(respective roots are: " << unionFind->find(term1)->toString() << " and " <<
        unionFind->find(term2)->toString() << ")";
    throw UnificationError(s.str().c_str());
}

bool Unifier::isTermVar(std::shared_ptr<Term> term) {
     return std::dynamic_pointer_cast<Var>(term) != nullptr;
}

bool Unifier::isProperType(std::shared_ptr<Term> term) {
    return std::dynamic_pointer_cast<Var>(term) == nullptr;
}

bool Unifier::isCons(std::shared_ptr<Term> term) {
    return std::dynamic_pointer_cast<Cons>(term) != nullptr;
}
