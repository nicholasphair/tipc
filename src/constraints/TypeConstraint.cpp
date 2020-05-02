#include "TypeConstraint.h"

std::string TypeConstraint::toString() {
    return lhs->toString() + " = " + rhs->toString();
}

bool TypeConstraint::operator==(const TypeConstraint &other) const {
    return *lhs == *(other.lhs);
}

bool TypeConstraint::operator!=(const TypeConstraint &other) const {
    return !(*this == other);
}
