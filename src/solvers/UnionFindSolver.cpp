#include "UnionFindSolver.hpp"
#include "Cons.hpp"
#include <iostream>
#include "UnificationError.hpp"
#include <sstream>

UnionFindSolver::~UnionFindSolver() {
    delete unionFind;
}

void UnionFindSolver::solve() {
    std::cout << "solving" << std::endl;
    unionFind->print_edges();
    for(TypeConstraint constraint: constraints) {
        std::cout << "--------------------" << std::endl;
        unify(constraint.lhs, constraint.rhs);
        unionFind->print_edges();
    }
    std::cout << "--------------------" << std::endl;
    std::cout << "done solving" << std::endl;
    unionFind->print_edges();
}

void UnionFindSolver::unify(Term *term1, Term *term2) {
    std::cout << "unifying " << term1->toString() << " and " << term2->toString() << std::endl;
    auto rep1 = unionFind->find(term1);
    auto rep2 = unionFind->find(term2);

    if(rep1 == nullptr || rep2 == nullptr) {
        throw UnificationError("one or both of these terms is not in the structure");
    }

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
     return dynamic_cast<Var *>(term) != nullptr;
}

bool UnionFindSolver::isProperType(Term * term) {
    return dynamic_cast<Var *>(term) == nullptr;
}

bool UnionFindSolver::isCons(Term * term) {
    return dynamic_cast<Cons *>(term) != nullptr;
}
