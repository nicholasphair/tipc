#ifndef TIPC_TYPECONSTRAINT_H
#define TIPC_TYPECONSTRAINT_H

#include <term.hpp>

class TypeConstraint {
public:
    TypeConstraint(Term * l, Term * r): lhs(l), rhs(r) {};
    std::string toString();
    Term * lhs;
    Term * rhs;
};


#endif //TIPC_TYPECONSTRAINT_H
