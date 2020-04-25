#include "tip_function.hpp"
#include "var.hpp"
#include "assert.h"

TipFunction::TipFunction() {
    assert(0);
}

TipFunction::TipFunction(std::vector<Term *> params, Term *ret) {
    this->params = params;
    this->ret = ret;
    this->arguments.insert(this->params.begin(), ret);
}

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
    // TODO: figure out how to print generic terms...
    // Does scala use the to string method?
    std::string str = "(";
    for(auto p : this->params) {
        str += "p";
        str += ",";
    }
    str += ") -> ";
    str += "*this->ret";
    return str;
}

bool TipFunction::is_concrete() {
    return true;
}
