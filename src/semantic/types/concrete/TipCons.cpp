#include "TipCons.h"

int TipCons::arity() const {
    return arguments.size();
}

bool TipCons::doMatch(TipType const * t) const {
    if(TipCons const * c = dynamic_cast<TipCons const *>(t)) {
        return c->arity() == arity();
    }
    return false;
}

TipCons::TipCons(std::vector<std::shared_ptr<TipType>> arguments) : arguments(std::move(arguments)) { }

const std::vector<std::shared_ptr<TipType>> &TipCons::getArguments() const {
    return arguments;
}
