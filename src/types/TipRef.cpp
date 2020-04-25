#include "TipRef.hpp"

TipRef::TipRef() {
    assert(0);
}

TipRef::TipRef(Term *of) {
    this->of = of;
    this->arguments.push_back(of);
}

Term *TipRef::substitute(Term *var, Term *term) {
    if(Var * sv = dynamic_cast<Var *>(var)) {
        return new TipRef(this->of->substitute(var, term));
    }
    assert(0);
}

std::string TipRef::toString() {
    // TODO: How the hell does scala print terms??
    return "&of";
}
