#pragma once

#include "Term.h"

class TypeConstraint {
public:
    TypeConstraint() = delete;
    TypeConstraint(std::shared_ptr<Term> l, std::shared_ptr<Term> r);

    std::shared_ptr<Term> lhs;
    std::shared_ptr<Term> rhs;
    bool operator==(const TypeConstraint& other) const;
    bool operator!=(const TypeConstraint& other) const;
    friend std::ostream& operator<<(std::ostream& os, const TypeConstraint& obj);
};

