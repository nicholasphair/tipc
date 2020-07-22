#include "TipInt.h"
#include "Var.h"
#include "assert.h"
#include <iostream>

TipInt::TipInt() { }

std::shared_ptr<Term> TipInt::substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) {
    if(Var * v = dynamic_cast<Var *>(v)) {
        // TODO: Not yet implemented.
        //return this;
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
