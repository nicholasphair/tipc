#pragma once

#include "TipType.h"
#include "Cons.h"
#include <string>
#include <vector>

class TipFunction: public TipType, public Cons {
public:
    TipFunction() = delete;
    TipFunction(std::vector<std::shared_ptr<Term>> params, std::shared_ptr<Term> ret);

    std::string toString() override;

    std::vector<std::shared_ptr<Term>> params;
    std::shared_ptr<Term> ret;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};

