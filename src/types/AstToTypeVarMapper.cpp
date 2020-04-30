#include "AstToTypeVarMapper.h"
#include "tip_var.hpp"
#include "../TIPtree.h"
//return std::map<Term *, std::vector<Term *>>();
// TODO: Figure out how to map...

Var *AstToTypeVarMapper::toTypeVar(TIPtree::Node node) {
    if(TIPtree::VariableExpr * v = dynamic_cast<TIPtree::VariableExpr *>(&node)) {
        // Find the correcponding declaration and make a tip var out
        // of that...
        return new TipVar(v);
    } else {
        return new TipVar(&node);
    }
}
