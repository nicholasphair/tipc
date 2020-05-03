#include "TipFunction.hpp"
#include "Var.hpp"
#include "assert.h"
#include <sstream>

Term *TipFunction::substitute(Term *var, Term *term) {
    if(Var * sv = dynamic_cast<Var *>(var)) {
        std::vector<Term *> new_params;
        for (auto p : this->params) {
            new_params.push_back(p->substitute(var, term));
        }
        auto new_ret = ret->substitute(var, term);
        return new TipFunction(new_params, new_ret);
    }
    assert(0);
}

std::string TipFunction::toString() {
    std::stringstream fmt;
    fmt << "(";
    int i = 0;
    for(auto p : params) {
        fmt << p->toString() << (++i == params.size() ? "" : ",");
    }
    fmt << ") -> " << ret->toString();
    return fmt.str();
}

bool TipFunction::operator==(const Term &other) const {
    if(auto tipFunction = dynamic_cast<const TipFunction *>(&other)) {
        if(arguments.size() != tipFunction->arguments.size()) {
            return false;
        }

        for(int i = 0; i < arguments.size(); i++) {
            if(*(arguments.at(i)) != *(tipFunction->arguments.at(i))) {
                return false;
            }
        }

        return *ret == *(tipFunction->ret);
    }
    return false;
}

bool TipFunction::operator!=(const Term &other) const {
    return !(*this == other);
}
