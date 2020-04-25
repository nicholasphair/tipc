#include "var.hpp"

Var::Var() {
    fv.insert(this);
}

std::set<Term *> Var::free_variables() {
    return fv;
}

Term * Var::substitute(Term * var, Term * term) {
    // will this ever return true? or do i need to cast to var?
    if(var == this) {
        return term;
    } else {
        return this;
    }
}
