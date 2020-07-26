#pragma once
#include <string>
#include "TipType.h"
#include "../../AST.h"
#include <iostream>

class TipVar: public TipType {
public:
    TipVar() = default;
    TipVar(AST::Node * node);

    AST::Node * node;
    bool operator==(const TipType& other) const override;
    bool operator!=(const TipType& other) const override;
    std::ostream& print(std::ostream &out) const override;
};
