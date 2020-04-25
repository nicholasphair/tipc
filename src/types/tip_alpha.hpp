#ifndef TIPC_TIP_ALPHA_HPP
#define TIPC_TIP_ALPHA_HPP

#include "TipType.hpp"
#include "cons.hpp"
#include <string>
#include <any>

class TipAlpha: public TipType, public Var {
public:
    TipAlpha();
    TipAlpha(std::any x);
    std::string toString();
    bool is_concrete() override;
    std::any x;

};


#endif //TIPC_TIP_ALPHA_HPP
