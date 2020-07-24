#pragma once

#include "TipType.h"
#include "TipCons.h"
#include <string>
#include <vector>

class TipFunction: public TipCons {
public:
    TipFunction() = delete;
    TipFunction(std::vector<std::shared_ptr<TipType>> params, std::shared_ptr<TipType> ret);

    std::string toString() override;

    std::vector<std::shared_ptr<TipType>> params;
    std::shared_ptr<TipType> ret;
    virtual int arity() override;
    bool operator==(const TipType& other) const override;
    bool operator!=(const TipType& other) const override;
};

