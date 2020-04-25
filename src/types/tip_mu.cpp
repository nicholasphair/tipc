#include "tip_mu.hpp"
#include "assert.h"

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

bool TipMu::is_concrete() {
    return true;
}
