#include "UnionFindSolver.hpp"
#include "cons.hpp"
#include <iostream>
#include "UnificationError.hpp"
#include <sstream>

UnionFindSolver::~UnionFindSolver() {
    delete unionFind;
}

void UnionFindSolver::solve() {
    for(TypeConstraint constraint: constraints) {
        unify(constraint.lhs, constraint.rhs);
    }
}

void UnionFindSolver::unify(Term *term1, Term *term2) {
    std::cout << "unifying t1 and t1" << std::endl;
    auto rep1 = unionFind->find(term1);
    auto rep2 = unionFind->find(term2);

    if(rep1 == nullptr || rep2 == nullptr) {
        throw UnificationError("one or both of these terms is not in the structure");
    }

    if(rep1 == rep2) {
       return;
    }

    if(isTermVar(term1) && isTermVar(term1)) {
        unionFind->quick_union(term1, term2);
    } else if(isTermVar(term1) && isProperType(term2)) {
        unionFind->quick_union(term1, term2);
    } else if(isProperType(term1) && isTermVar(term2)) {
        unionFind->quick_union(term2, term1);
    } else if(isCons(term1) && isCons(term2)) {
        auto f1 = dynamic_cast<Cons *>(term1);
        auto f2 = dynamic_cast<Cons *>(term2);
        if(!f1->do_match(f2)) {
            throwUnifyException(f1, f2);
        }

        unionFind->quick_union(term1, term2);
        for(int i = 0; i < f1->arguments.size(); i++) {
            auto a1 = f1->arguments.at(i);
            auto a2 = f2->arguments.at(i);
            std::cout << "Unifying subterms " << a1->toString() << " and " << a2->toString();
            unify(a1, a2);
        }
    } else {
        throwUnifyException(term1, term2);
    }
}

void UnionFindSolver::throwUnifyException(Term * term1, Term * term2) {
    std::stringstream s;
    s << "Cannot unify " << term1->toString() << "and " << term2->toString();
    throw UnificationError(s.str().c_str());
}

bool UnionFindSolver::isTermVar(Term * term) {
    bool b =  dynamic_cast<Var *>(term) != nullptr;
    return b;
}

bool UnionFindSolver::isProperType(Term * term) {
    bool b = dynamic_cast<Var *>(term) == nullptr && dynamic_cast<Cons *>(term) == nullptr;
    return b;
}

bool UnionFindSolver::isCons(Term * term) {
    bool b = dynamic_cast<Cons *>(term) != nullptr;
    return b;
}




