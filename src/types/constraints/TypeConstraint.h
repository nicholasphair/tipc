#pragma once

#include "Term.h"

class TypeConstraint {
public:
    TypeConstraint() = delete;
    TypeConstraint(Term * l, Term * r): lhs(l), rhs(r) {};

    Term * lhs;
    Term * rhs;
    bool operator==(const TypeConstraint& other) const;
    bool operator!=(const TypeConstraint& other) const;
    friend std::ostream& operator<<(std::ostream& os, const TypeConstraint& obj);
};

