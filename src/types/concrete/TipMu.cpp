#include "TipMu.h"
#include "assert.h"
#include <iostream>

TipMu::TipMu() {
    assert(0);
}

TipMu::TipMu(Var *v, Term *t) {
    this->v = v;
    this->t = t;
}

Term * TipMu::substitute(Term *var, Term *term) {
    if(Var * sv = dynamic_cast<Var *>(v)) {
        if(sv == this->v) {
            return this;
        } else {
            return new TipMu(this->v, this->t->substitute(sv, term));
        }
    }
    assert(0);
}

std::string TipMu::toString() {
    return "";
}

bool TipMu::operator==(const Term &other) const {
    if(auto mu = dynamic_cast<const TipMu *>(&other)) {
        return *v == *(mu->v) && *t == *(mu->t);
    }
    return false;
}

bool TipMu::operator!=(const Term &other) const {
    return !(*this == other);
}
