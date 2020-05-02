#ifndef TIPC_TIPMU_HPP
#define TIPC_TIPMU_HPP
#include <string>
#include "TipType.hpp"
#include "Mu.hpp"
#include "Var.hpp"
#include "Term.hpp"
#include "../TIPtree.h"

class TipMu: public TipType, public Mu {
public:
    TipMu();
    TipMu(Var * v, Term * t);
    Term * substitute(Term * var, Term * term) override;
    std::string toString() override ;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;

    Var * v;
    Term * t;
};


#endif //TIPC_TIPMU_HPP
