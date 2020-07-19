#pragma once
#include "TipType.h"
#include "Cons.h"

class TipRef: public TipType, public Cons {
public:
    TipRef() = delete;
    TipRef(Term * of): of(of) { arguments.push_back(of); };

    Term * substitute(Term * var, Term * term) override;
    std::string toString() override ;

    Term * of;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};


