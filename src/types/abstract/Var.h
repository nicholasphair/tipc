#pragma once

#include "Term.h"

/**
 * A Constraint Variable.
 */
class Var: public Term {
public:
    Var();
    std::set<std::shared_ptr<Term>> free_variables() override;
    std::shared_ptr<Term> substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) override;
private:
    std::set<std::shared_ptr<Term>> fv;
};


