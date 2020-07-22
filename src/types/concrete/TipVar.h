#pragma once
#include <string>
#include "TipType.h"
#include "Var.h"
#include "../../AST.h"
#include <iostream>

class TipVar: public TipType, public Var {
public:
    TipVar() = delete;
    TipVar(AST::Node * node) : node(node) {};
    TipVar(std::shared_ptr<AST::Node> node);

    std::string toString() override;
    std::shared_ptr<AST::Node> node;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};

