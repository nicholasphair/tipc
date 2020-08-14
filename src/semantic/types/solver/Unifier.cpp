#include "TipCons.h"
#include "UnificationError.h"
#include "Unifier.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

Unifier::Unifier() : unionFind(std::move(std::make_unique<UnionFind<TipType>>())) {}

Unifier::Unifier(std::vector<TypeConstraint> constrs) : constraints(std::move(constrs)) {
    std::vector<TipType *> types;
    for(TypeConstraint& constraint : constraints) {
        auto lhs = constraint.lhs.get();
        auto rhs = constraint.rhs.get();
        types.push_back(lhs);
        types.push_back(rhs);

        if(auto f1 = dynamic_cast<TipCons *>(lhs)) {
            for(auto &a : f1->getArguments()) {
                types.push_back(a.get());
            }
        }
        if(auto f2 = dynamic_cast<TipCons *>(rhs)) {
            for(auto &a : f2->getArguments()) {
                types.push_back(a.get());
            }
        }
    }

    std::vector<TipType *> unique = std::move(deduplicate(types));
    std::cout << "size of unique: " << unique.size() << std::endl;
    unionFind = std::make_unique<UnionFind<TipType>>(unique);
}

std::vector<TipType *> Unifier::deduplicate(std::vector<TipType *> types) {
    std::vector<TipType *> unique;
    for(auto &type : types) {
        bool add = true;
        for(auto &u : unique) {
            if(*type == *u) {
                add = false;
            }
        }
        if(add) {
            unique.push_back(type);
        }
    }
    return unique;
}

void Unifier::solve() {
    for(TypeConstraint &constraint: constraints) {
        unify(constraint.lhs.get(), constraint.rhs.get());
    }
}

void Unifier::unify(TipType const * TipType1, TipType const * TipType2) {
    auto rep1 = unionFind->find(TipType1);
    auto rep2 = unionFind->find(TipType2);

    if(rep1 == rep2) {
       return;
    }

    if(isTypeVariable(rep1) && isTypeVariable(rep2)) {
        unionFind->quick_union(rep1, rep2);
    } else if(isTypeVariable(rep1) && isProperType(rep2)) {
        unionFind->quick_union(rep1, rep2);
    } else if(isProperType(rep1) && isTypeVariable(rep2)) {
        unionFind->quick_union(rep2, rep1);
    } else if(isCons(rep1) && isCons(rep2)) {
        auto f1 = dynamic_cast<TipCons const *>(rep1);
        auto f2 = dynamic_cast<TipCons const *>(rep2);
        if(!f1->doMatch(f2)) {
            throwUnifyException(f1, f2);
        }

        unionFind->quick_union(rep1, rep2);
        for(int i = 0; i < f1->getArguments().size(); i++) {
            auto a1 = f1->getArguments().at(i).get();
            auto a2 = f2->getArguments().at(i).get();
            unify(a1, a2);
        }
    } else {
        throwUnifyException(TipType1, TipType2);
    }
}

void Unifier::throwUnifyException(TipType const * TipType1, TipType const * TipType2) {
    std::stringstream s;
    s << "Cannot unify " << TipType1 << "and " << TipType2 <<
        "(respective roots are: " << unionFind->find(TipType1) << " and " <<
        unionFind->find(TipType2) << ")";
    throw UnificationError(s.str().c_str());
}

bool Unifier::isTypeVariable(TipType const * TipType) {
     return dynamic_cast<TipVar const *>(TipType) != nullptr;
}

bool Unifier::isProperType(TipType const * TipType) {
    return dynamic_cast<TipVar const *>(TipType) == nullptr;
}

bool Unifier::isCons(TipType const * TipType) {
    return dynamic_cast<TipCons const *>(TipType) != nullptr;
}

