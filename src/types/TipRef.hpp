#ifndef TIPC_TIPREF_HPP
#define TIPC_TIPREF_HPP
#include "TipType.hpp"
#include "cons.hpp"

class TipRef: public TipType, public Cons {
public:
    TipRef();
    TipRef(Term * of);

    Term * substitute(Term * var, Term * term) override;
    bool is_concrete() override;
    std::string toString();

    Term * of;
};


#endif //TIPC_TIPREF_H
