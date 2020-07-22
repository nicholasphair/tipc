#pragma once
#include "TipType.h"
#include "Cons.h"

class TipRef: public TipType, public Cons {
public:
    TipRef() = delete;
    TipRef(std::shared_ptr<Term> of);

    std::shared_ptr<Term> substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) override;
    std::string toString() override ;

    //Term * of;
    std::shared_ptr<Term> of;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};


