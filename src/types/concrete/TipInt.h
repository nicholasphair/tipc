#pragma once

#include "TipType.h"
#include "Cons.h"
#include <string>

class TipInt: public TipType, public Cons {
public:
    TipInt();
    Term * substitute(Term * var, Term * term) override;
    std::string toString() override;

    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};

