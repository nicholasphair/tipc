#pragma once

#include "../../AST.h"
#include <string>

class TipType {
public:
    virtual std::string toString() = 0;
    virtual bool operator==(const TipType& other) const = 0;
    virtual bool operator!=(const TipType& other) const = 0;
};


