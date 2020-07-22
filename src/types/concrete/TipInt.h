#pragma once

#include "TipType.h"
#include "Cons.h"
#include <string>

class TipInt: public TipType, public Cons {
public:
    TipInt();
    std::shared_ptr<Term> substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) override;
    std::string toString() override;

    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};

