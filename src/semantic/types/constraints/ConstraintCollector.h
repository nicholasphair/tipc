#pragma once
#include "ConstraintHandler.h"
#include "TypeConstraint.h"


class ConstraintCollector: public ConstraintHandler {
public:
    void handle(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2) override;
    std::vector<TypeConstraint>& getCollectedConstraints();
private:
    std::vector<TypeConstraint> collected;

};

