#include "TipInt.h"

TipInt::TipInt() { }

std::string TipInt::toString() {
    return "int";
}

bool TipInt::operator==(const TipType &other) const {
    if(auto t = dynamic_cast<TipInt const *>(&other)) {
        return true;
    }
    return false;
}

bool TipInt::operator!=(const TipType &other) const {
    return !(*this == other);
}
