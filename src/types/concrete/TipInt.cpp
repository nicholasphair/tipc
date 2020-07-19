#include "TipInt.h"
#include "Var.h"
#include "assert.h"
#include <iostream>

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

bool TipInt::operator==(const Term &other) const {
    if(auto t = dynamic_cast<TipInt const *>(&other)) {
        return true;
    }
    return false;
}

bool TipInt::operator!=(const Term &other) const {
    return !(*this == other);
}
