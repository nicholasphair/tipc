#include "TipRef.hpp"
#include "Var.hpp"
#include <sstream>

Term *TipRef::substitute(Term *var, Term *term) {
    if(Var * sv = dynamic_cast<Var *>(var)) {
        return new TipRef(this->of->substitute(var, term));
    }
    assert(0);
}

std::string TipRef::toString() {
    std::stringstream stream;
    stream << "&" << of->toString();
    return stream.str();
}

bool TipRef::operator==(const Term &other) const {
    if(auto t = dynamic_cast<const TipRef *>(&other)) {
        return *of == *(t->of);
    }
    return false;
}

bool TipRef::operator!=(const Term &other) const {
    return !(*this == other);
}
