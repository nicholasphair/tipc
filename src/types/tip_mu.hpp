#ifndef TIPC_TIP_MU_HPP
#define TIPC_TIP_MU_HPP
#include <string>
#include "TipType.hpp"
#include "mu.hpp"
#include "var.hpp"
#include "term.hpp"
#include "../TIPtree.h"

class TipMu: public TipType, public Mu {
public:
    TipMu();
    TipMu(Var * v, Term * t);
    Term * substitute(Term * var, Term * term) override;
    bool is_concrete() override;

    Var * v;
    Term * t;
};


#endif //TIPC_TIP_MU_HPP
