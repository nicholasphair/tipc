#include "Cons.h"
#include "Var.h"

int Cons::arity() {
    return arguments.size();
}

bool Cons::do_match(std::shared_ptr<Term> t) {
    if(Cons * c = dynamic_cast<Cons *>(t.get())) {
        return c->arity() == arity();
    }
    return false;
}
