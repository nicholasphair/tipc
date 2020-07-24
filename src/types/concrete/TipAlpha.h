#pragma once

#include "TipVar.h"
#include "TipCons.h"
#include <string>
#include <any>

class TipAlpha: public TipVar {
public:
    TipAlpha() = default;
    TipAlpha(std::string x);
    std::string toString() override;
    virtual bool operator==(const TipType& other) const override;
    virtual bool operator!=(const TipType& other) const override;

private:
    std::string x;

};


