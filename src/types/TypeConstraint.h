#ifndef TIPC_TYPECONSTRAINT_H
#define TIPC_TYPECONSTRAINT_H

#include "TipType.hpp"

class TypeConstraint {
public:
    TypeConstraint(TipType * l, TipType * r): lhs(l), rhs(r) {};
    std::string toString();
private:
    TipType * lhs;
    TipType * rhs;
};


#endif //TIPC_TYPECONSTRAINT_H
