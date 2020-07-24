#pragma once
#include "TipType.h"
#include "TipCons.h"

class TipRef: public TipCons {
public:
    TipRef() = delete;
    TipRef(std::shared_ptr<TipType> of);

    std::string toString() override ;

    std::shared_ptr<TipType> of;
    bool operator==(const TipType& other) const override;
    bool operator!=(const TipType& other) const override;
};


