#pragma once

#include <string>
#include "TipType.h"
#include "Mu.h"
#include "Var.h"
#include "Term.h"
#include "../../AST.h"

class TipMu: public TipType, public Mu {
public:
    TipMu();
    TipMu(Var * v, Term * t);
    Term * substitute(Term * var, Term * term) override;
    std::string toString() override ;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;

    Var * v;
    Term * t;
};


