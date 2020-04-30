#ifndef TIPC_UNIONFINDSOLVER_HPP
#define TIPC_UNIONFINDSOLVER_HPP
#include "term.hpp"
#include "var.hpp"
#include <string>
#include <map>
#include <vector>

class UnionFindSolver {
public:
    UnionFindSolver();
    Term * find(Term * t);
    std::map<Var *, Term *> solution();
    std::string toString();
    std::map<Term *, std::vector<Term *>> unifications();
    void unify(Term * t1, Term * t2);
private:
    void mkUnion(Term * t1, Term * t2);
    void mkSet(Term * t);
    std::map<Term *, Term *> parent;
};


#endif //TIPC_UNIONFINDSOLVER_HPP
