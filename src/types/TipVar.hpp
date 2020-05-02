#ifndef TIPC_TIPVAR_HPP
#define TIPC_TIPVAR_HPP
#include <string>
#include "TipType.hpp"
#include "Var.hpp"
#include "../TIPtree.h"
#include <iostream>

class TipVar: public TipType, public Var {
public:
    TipVar() = delete;
    TipVar(TIPtree::Node * node): node(node) {};

    std::string toString() override;
    TIPtree::Node * node ;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};


#endif //TIPC_TIPVAR_HPP
