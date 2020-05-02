#ifndef TIPC_TIPALPHA_HPP
#define TIPC_TIPALPHA_HPP

#include "TipType.hpp"
#include "Cons.hpp"
#include <string>
#include <any>
#include "Var.hpp"

class TipAlpha: public TipType, public Var {
public:
    TipAlpha() = default;
    TipAlpha(std::any x): x(std::move(x)) {};
    std::string toString() override;
    virtual bool operator==(const Term& other) const override;
    virtual bool operator!=(const Term& other) const override;

private:
    std::any x;

};


#endif //TIPC_TIPALPHA_HPP
