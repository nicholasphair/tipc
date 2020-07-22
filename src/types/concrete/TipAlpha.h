#pragma once

#include "TipType.h"
#include "Cons.h"
#include <string>
#include <any>
#include "Var.h"

class TipAlpha: public TipType, public Var {
public:
    TipAlpha() = default;
    TipAlpha(std::string x);
    std::string toString() override;
    virtual bool operator==(const Term& other) const override;
    virtual bool operator!=(const Term& other) const override;

private:
    std::string x;

};


