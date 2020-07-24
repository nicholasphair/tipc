#pragma once

#include "TipType.h"
#include "TipCons.h"
#include <string>

class TipInt: public TipCons {
public:
    TipInt();
    std::string toString() override;

    bool operator==(const TipType& other) const override;
    bool operator!=(const TipType& other) const override;
};

