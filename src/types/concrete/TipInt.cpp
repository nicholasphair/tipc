#include "TipInt.h"
#include "Var.h"
#include "assert.h"
#include <iostream>

TipInt::TipInt() { }

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
