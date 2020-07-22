#include "TipRef.h"
#include "Var.h"
#include <sstream>

TipRef::TipRef(std::shared_ptr<Term> of): of(of) {
    // TODO: Not yet implemented
    //arguments.push_back(of.get());
}

std::shared_ptr<Term> TipRef::substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) {
    // TODO: Not yet implemented
    assert(0);
    //if(Var * sv = dynamic_cast<Var *>(var)) {
    //    return new TipRef(this->of->substitute(var, term));
    //}
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
