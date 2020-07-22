#include "Cons.h"
#include "Var.h"

int Cons::arity() {
    return arguments.size();
}

std::set<std::shared_ptr<Term>> Cons::free_variables() {
    std::set<std::shared_ptr<Term>> fv;
    for(auto t : arguments) {
        auto cfv = t->free_variables();
        fv.insert(cfv.begin(), cfv.end());
    }
    return fv;
}

bool Cons::do_match(std::shared_ptr<Term> t) {
    if(Cons * c = dynamic_cast<Cons *>(t.get())) {
        return c->arity() == arity();
    }
    return false;
}
