#include "TipCons.h"
#include "UnificationError.h"
#include "Unifier2.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

Unifier2::Unifier2() : unionFind(std::move(std::make_unique<UnionFind2>())) {}

Unifier2::Unifier2(std::vector<TypeConstraint> constrs) : constraints(std::move(constrs)) {
    std::vector<std::shared_ptr<TipType>> types;
    for(TypeConstraint& constraint : constraints) {
        auto lhs = constraint.lhs;
        auto rhs = constraint.rhs;
        types.push_back(lhs);
        types.push_back(rhs);

        if(auto f1 = std::dynamic_pointer_cast<TipCons>(lhs)) {
            for(auto &a : f1->getArguments()) {
                types.push_back(a);
            }
        }
        if(auto f2 = std::dynamic_pointer_cast<TipCons>(rhs)) {
            for(auto &a : f2->getArguments()) {
                types.push_back(a);
            }
        }
    }

    std::vector<std::shared_ptr<TipType>> unique = std::move(deduplicate(types));
    std::cout << "size of unique: " << unique.size() << std::endl;
    unionFind = std::make_unique<UnionFind2>(unique);
}

std::vector<std::shared_ptr<TipType>> Unifier2::deduplicate(std::vector<std::shared_ptr<TipType>> types) {
    std::vector<std::shared_ptr<TipType>> unique;
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

void Unifier2::solve() {
    for(TypeConstraint &constraint: constraints) {
        unify(constraint.lhs, constraint.rhs);
    }
}

void Unifier2::unify(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2) {
    std::cout << "unifying " << *t1 << " with " << *t2 << std::endl;
    auto rep1 = unionFind->find(t1);
    auto rep2 = unionFind->find(t2);

    if(rep1 == rep2) {
       return;
    }

    if(isTypeVariable(rep1) && isTypeVariable(rep2)) {
        std::cout << "2 types vars" << std::endl;
        unionFind->quick_union(rep1, rep2);
    } else if(isTypeVariable(rep1) && isProperType(rep2)) {
        std::cout << "types var and proper type" << std::endl;
        unionFind->quick_union(rep1, rep2);
    } else if(isProperType(rep1) && isTypeVariable(rep2)) {
        std::cout << "proper type and type var" << std::endl;
        unionFind->quick_union(rep2, rep1);
    } else if(isCons(rep1) && isCons(rep2)) {
        std::cout << "2 cons" << std::endl;
        auto f1 = std::dynamic_pointer_cast<TipCons>(rep1);
        auto f2 = std::dynamic_pointer_cast<TipCons>(rep2);
        if(!f1->doMatch(f2.get())) {
            throwUnifyException(t1,t2);
        }

        unionFind->quick_union(rep1, rep2);
        for(int i = 0; i < f1->getArguments().size(); i++) {
            auto a1 = f1->getArguments().at(i);
            auto a2 = f2->getArguments().at(i);
            unify(a1, a2);
        }
    } else {
        throwUnifyException(t1,t2);
    }
}

void Unifier2::throwUnifyException(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2) {
    std::stringstream s;
    s << "Cannot unify " << *t1 << "and " << *t2 <<
        "(respective roots are: " << unionFind->find(t1) << " and " <<
        unionFind->find(t2) << ")";
    throw UnificationError(s.str().c_str());
}

bool Unifier2::isTypeVariable(std::shared_ptr<TipType> type) {
    return std::dynamic_pointer_cast<TipVar>(type) != nullptr;
}

bool Unifier2::isProperType(std::shared_ptr<TipType> type) {
    return std::dynamic_pointer_cast<TipVar>(type) == nullptr;
}

bool Unifier2::isCons(std::shared_ptr<TipType> type) {
    return std::dynamic_pointer_cast<TipCons>(type) != nullptr;
}


