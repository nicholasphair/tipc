#pragma once

#include <memory>
#include <TipType.h>

class ConstraintHandler {
public:
    virtual ~ConstraintHandler() = default;
    virtual void handle(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2) = 0;
};