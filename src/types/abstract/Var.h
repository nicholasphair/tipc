#pragma once

#include "Term.h"

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


