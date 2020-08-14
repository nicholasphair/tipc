#pragma once

#include "ConstraintHandler.h"
#include "TypeConstraint.h"
#include "Unifier2.h"


class ConstraintUnifier: public ConstraintHandler {
public:
    void handle(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2) override;

private:
    int i = 1;
    Unifier2 unifier;

};

