#ifndef TIPC_TIP_INT_HPP
#define TIPC_TIP_INT_HPP

#include "TipType.hpp"
#include "cons.hpp"
#include <string>

class TipInt: public TipType, public Cons {
public:
    TipInt();
    Term * substitute(Term * var, Term * term) override;
    std::string toString();
    bool is_concrete() override;

};


#endif //TIPC_TIP_INT_HPP
