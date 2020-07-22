#pragma once

#include "Term.h"
#include <set>
#include <vector>

class Cons: public Term {
public:
    std::set<std::shared_ptr<Term>> free_variables() override;
    std::vector<std::shared_ptr<Term>> arguments;
    virtual int arity();
    bool do_match(std::shared_ptr<Term> t);
};

