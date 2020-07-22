#include "TipFunction.h"
#include "Var.h"
#include "assert.h"
#include <sstream>

TipFunction::TipFunction(std::vector<std::shared_ptr<Term>> params, std::shared_ptr<Term> ret): params(params), ret(ret) {
    for(auto p : params) {
        arguments.push_back(p);
    }
    this->arguments.push_back(ret);
};

std::shared_ptr<Term> TipFunction::substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) {
    if(Var * sv = dynamic_cast<Var *>(var.get())) {
        std::vector<std::shared_ptr<Term>> new_params;
        for (auto p : this->params) {
            // TODO: Not yet implemented.
            //new_params.push_back(p->substitute(var, term));
        }
        auto new_ret = ret->substitute(var, term);
        // TODO Note yet implemented..
        //return new TipFunction(new_params, new_ret);
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
