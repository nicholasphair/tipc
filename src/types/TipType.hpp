#ifndef TIPC_TIPTYPE_H
#define TIPC_TIPTYPE_H

#include "../TIPtree.h"
#include "var.hpp"

class TipType {
    // given an ast node and decl data gimme a var
    // TODO: Figure out the implicit ast2typevar
    Var * astToTypeVar(TIPtree::Node node);

};


#endif //TIPC_TIPTYPE_H
