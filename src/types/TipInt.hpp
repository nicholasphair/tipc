#ifndef TIPC_TIPINT_HPP
#define TIPC_TIPINT_HPP

#include "TipType.hpp"
#include "Cons.hpp"
#include <string>

class TipInt: public TipType, public Cons {
public:
    TipInt();
    Term * substitute(Term * var, Term * term) override;
    std::string toString() override;

    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};


#endif //TIPC_TIPINT_HPP
