#pragma once

#include "Term.h"
#include <set>
#include <vector>

class Cons: public Term {
public:
    std::set<Term *> free_variables() override;
    std::vector<Term *> arguments;
    virtual int arity();
    bool do_match(Term * t);
};

