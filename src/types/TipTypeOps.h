#ifndef TIPC_TIPTYPEOPS_H
#define TIPC_TIPTYPEOPS_H

#include "TermOps.hpp"


class TipTypeOps: public TermOps {
    Mu * make_mu(Var * var, Term * term);
    Var * make_alpha(Var * var);
};


#endif //TIPC_TIPTYPEOPS_H
