#pragma once

#include "TipType.h"
#include <set>
#include <vector>

class TipCons: public TipType {
public:
    std::vector<std::shared_ptr<TipType>> arguments;
    virtual int arity();
    bool do_match(std::shared_ptr<TipType> t);
};

