#ifndef TIPC_TYPECONSTRAINT_H
#define TIPC_TYPECONSTRAINT_H

#include <Term.hpp>

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


#endif //TIPC_TYPECONSTRAINT_H
