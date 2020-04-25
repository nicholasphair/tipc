#include <assert.h>
#include "var.hpp"

Var::Var() {
    fv.insert(this);
}

std::set<Term *> Var::free_variables() {
    return fv;
}

Term * Var::substitute(Term * var, Term * term) {
    if(Var * v = dynamic_cast<Var *>(v)) {
        if(var == this) {
            return term;
        } else {
            return this;
        }
    }
    assert(0);
}
