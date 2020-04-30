#include "UnionFindSolver.hpp"
#include "cons.hpp"
#include <iostream>
#include <assert.h>
#include "UnificationError.hpp"

UnionFindSolver::UnionFindSolver() {

}

Term *UnionFindSolver::find(Term *t) {
    mkSet(t);
    if(this->parent[t] != t) {
        auto p = this->parent[t];
        this->parent.insert(std::pair<Term *, Term *>(t, p));
    }
    return this->parent[t];
}

std::map<Var *, Term *> UnionFindSolver::solution() {
    // TODO:
    return std::map<Var *, Term *>();
}

std::string UnionFindSolver::toString() {
    std::string str;
    for(auto const &x : this->parent) {
        str += x.first->toString() + " + " + x.second->toString() += "\n";
    }
    return str;
}

std::map<Term *, std::vector<Term *>> UnionFindSolver::unifications() {
    std::vector<Term *> keys;
    for(auto it = this->parent.begin(); it !=this->parent.end(); ++it) {
        keys.push_back(it->first);
    }

    for(auto x : keys) {
        if(Var * v = dynamic_cast<Var *>(x)) {

        }
    }



    // TODO:
    return std::map<Term *, std::vector<Term *>>();
}

void UnionFindSolver::unify(Term *t1, Term *t2) {
    std::cout << "unifying t1 and t1" << std::endl;
    mkSet(t1);
    mkSet(t2);
    auto rep1 = find(t1);
    auto rep2 = find(t2);

    if(rep1 == rep2) {
       return;
    }

    Var * v1 = dynamic_cast<Var *>(rep1);
    Var * v2 = dynamic_cast<Var *>(rep2);
    Term * term1 = dynamic_cast<Term *>(rep1);
    Term * term2 = dynamic_cast<Term *>(rep2);
    Cons * f1 = dynamic_cast<Cons *>(rep1);
    Cons * f2 = dynamic_cast<Cons *>(rep2);

    if(v1 != nullptr && v2 != nullptr) {
        mkUnion(v1, v2);
    } else if(v1 != nullptr && term2 != nullptr) {
        mkUnion(v1, term2);
    } else if(term1 != nullptr && v2 != nullptr) {
        mkUnion(v2, term2);
    } else if(f1 != nullptr && f2 != nullptr && f1->do_match(f2)) {
        mkUnion(f1, f2);
        for(int i = 0; i < f1->arguments.size(); i++) {
            auto a1 = f1->arguments.at(i);
            auto a2 = f2->arguments.at(i);
            std::cout << "Unifying subterms " << a1->toString() << " and " << a2->toString();
            unify(a1, a2);
        }
    } else {
        std::string msg;
        msg += "Can't unify " + t1->toString() + "and " + t2->toString() +
                " ( with representatives " + rep1->toString() + " and " +
                rep2-> toString() + ")";
        throw UnificationError(msg.c_str());
    }
}

void UnionFindSolver::mkUnion(Term *t1, Term *t2) {
    this->parent.insert(std::pair<Term *, Term *>(t1, t2));
}

void UnionFindSolver::mkSet(Term *t) {
    if(this->parent.count(t) == 0) {
        this->parent.insert(std::pair<Term *, Term *>(t, t));
    }
}
