#include "TermOps.hpp"
#include "Cons.hpp"
#include "assert.h"

Term *TermOps::close(Term *term, std::map<Var *, Term *> env) {
    return closeRec(term, env);
}

Term *TermOps::closeRec(Term * term, std::map<Var *, Term *> env, std::set<Var *> visited) {
    if(Var * v = dynamic_cast<Var *>(term)) {
        if(visited.count(v) == 0 && env.at(v) != v) {
            // no cycle found, and the variable does not map to itself
            visited.insert(v);
            auto cterm = closeRec(env.at(v), env, visited);
            auto newV = make_alpha(v);
            if(cterm->free_variables().count(newV) != 0) {
                return make_mu(newV, cterm->substitute(v, newV));
            } else {
                return cterm;
            }
        } else {
            make_alpha(v);
        }
    } else if(Cons * c = dynamic_cast<Cons *>(term)) {
        for(auto v : c->free_variables()) {
            term->substitute(v, closeRec(v, env, visited));
        }
        return c;
    } else if(Mu * m = dynamic_cast<Mu *>(term)) {
        return make_mu(m->v, closeRec(m->t, env, visited));
    } else {
        assert(0);
    }
return nullptr;
}
