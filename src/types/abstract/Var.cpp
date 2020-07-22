#include <assert.h>
#include "Var.h"

Var::Var() {
    // TODO: Not yet implmented
    //fv.insert(this);
}

std::set<std::shared_ptr<Term>> Var::free_variables() {
    return fv;
}

std::shared_ptr<Term> Var::substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) {
    if(Var * v = dynamic_cast<Var *>(var.get())) {
        if(v == this) {
            return term;
        } else {
            // TODO: NOT YET IMPLEMENTED
            assert(0);
            //return std::make_shared<Var>(this);
        }
    }
    assert(0);
}
