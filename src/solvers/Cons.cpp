#include "Cons.hpp"
#include "Var.hpp"

int Cons::arity() {
    return arguments.size();
}

std::set<Term *> Cons::free_variables() {
    std::set<Term *> fv;
    for(auto t : arguments) {
        auto cfv = t->free_variables();
        fv.insert(cfv.begin(), cfv.end());
    }
    return fv;
}

bool Cons::do_match(Term *t) {
    if(Cons * c = dynamic_cast<Cons *>(t)) {
        return c->arity() == arity();
    }
    return false;
}
