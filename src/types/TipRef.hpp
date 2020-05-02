#ifndef TIPC_TIPREF_HPP
#define TIPC_TIPREF_HPP
#include "TipType.hpp"
#include "Cons.hpp"

class TipRef: public TipType, public Cons {
public:
    TipRef() = delete;
    TipRef(Term * of): of(of) { arguments.push_back(of); };

    Term * substitute(Term * var, Term * term) override;
    std::string toString() override ;

    Term * of;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};


#endif //TIPC_TIPREF_H
