#ifndef TIPC_VAR_HPP
#define TIPC_VAR_HPP
#include "term.hpp"

/**
 * A Constraint Variable.
 */
class Var: public Term {
public:
    Var();
    std::set<Term *> free_variables() override;
    Term * substitute(Term * var, Term * term) override;
private:
    std::set<Term *> fv;
};


#endif //TIPC_VAR_HPP
