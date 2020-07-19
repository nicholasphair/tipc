#pragma once
#include <string>
#include "TipType.h"
#include "Var.h"
#include "../../AST.h"
#include <iostream>

class TipVar: public TipType, public Var {
public:
    TipVar() = delete;
    TipVar(AST::Node * node): node(node) {};

    std::string toString() override;
    AST::Node * node ;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};

