#ifndef TIPC_TIP_FUNCTION_HPP
#define TIPC_TIP_FUNCTION_HPP

#include "TipType.hpp"
#include "cons.hpp"
#include <string>
#include <vector>

class TipFunction: public TipType, public Cons {
public:
    TipFunction();
    TipFunction(std::vector<Term *> params, Term * ret);
    Term * substitute(Term * var, Term * term) override;
    bool is_concrete() override;
    std::string toString() override;

    std::vector<Term *> params;
    Term * ret;
};

#endif
