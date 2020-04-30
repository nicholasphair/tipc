#ifndef TIPC_TIP_VAR_HPP
#define TIPC_TIP_VAR_HPP
#include <string>
#include "TipType.hpp"
#include "var.hpp"
#include "../TIPtree.h"

class TipVar: public TipType, public Var {
public:
    TipVar();
    explicit TipVar(TIPtree::Node * node);

    std::string toString() override;
    TIPtree::Node * node ;
    bool is_concrete() override;
};


#endif //TIPC_TIP_VAR_HPP
