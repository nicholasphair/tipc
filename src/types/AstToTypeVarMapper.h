#ifndef TIPC_ASTTOTYPEVARMAPPER_H
#define TIPC_ASTTOTYPEVARMAPPER_H
#include "../TIPtree.h"
#include "var.hpp"


class AstToTypeVarMapper {
    Var * toTypeVar(TIPtree::Node node);
};


#endif //TIPC_ASTTOTYPEVARMAPPER_H
