#include "TipCons.h"

int TipCons::arity() {
    return arguments.size();
}

bool TipCons::do_match(std::shared_ptr<TipType> t) {
    if(TipCons * c = dynamic_cast<TipCons *>(t.get())) {
        return c->arity() == arity();
    }
    return false;
}
