#include "tip_int.hpp"
#include "var.hpp"
#include "assert.h"

TipInt::TipInt() { }

Term * TipInt::substitute(Term *var, Term *term) {
    if(Var * v = dynamic_cast<Var *>(v)) {
        return this;
    }
    assert(0);
}

std::string TipInt::toString() {
    return "int";
}

bool TipInt::is_concrete() {
    return true;
}

