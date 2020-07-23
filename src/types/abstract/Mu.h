#pragma once

#include "Term.h"
#include "Var.h"
#include <string>

class Mu: public Term {

public:
    std::shared_ptr<Var> v;
    std::shared_ptr<Term> t;

    virtual std::string toString() override;
};

