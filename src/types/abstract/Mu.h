#pragma once

#include "Term.h"
#include "Var.h"
#include <string>

class Mu: public Term {

public:
    Var * v;
    Term * t;

    std::set<Term *> free_variables() override;
    virtual std::string toString() override;
};

