#ifndef TIPC_TERM_OPS_HPP
#define TIPC_TERM_OPS_HPP
#include "term.hpp"
#include "var.hpp"
#include "mu.hpp"
#include <map>
#include <set>

class term_ops {
public:
    virtual Mu * make_mu(Var * var, Term * term) = 0;
    virtual Var * make_alpha(Var * var) = 0;

    virtual Term * close(Term * term, std::map<Var *, Term *> env);

    virtual Term * closeRec(Term * term, std::map<Var *, Term *> env, std::set<Var *> visited = std::set<Var *>());

};


#endif //TIPC_TERM_OPS_HPP
