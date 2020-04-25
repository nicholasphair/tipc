#ifndef TIPC_TIPTYPEOPS_H
#define TIPC_TIPTYPEOPS_H

#include "term_ops.hpp"


class TipTypeOps: public term_ops {
    Mu * make_mu(Var * var, Term * term);
    Var * make_alpha(Var * var);
};


#endif //TIPC_TIPTYPEOPS_H
