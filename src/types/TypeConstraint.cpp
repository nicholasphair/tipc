#include "TypeConstraint.h"

std::string TypeConstraint::toString() {
    return lhs->toString() + " = " + rhs->toString();
}
