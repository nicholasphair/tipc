#pragma once

#include "TipType.h"
#include "Cons.h"
#include <string>
#include <vector>

class TipFunction: public TipType, public Cons {
public:
    TipFunction() = delete;
    TipFunction(std::vector<Term *> params, Term * ret): params(std::move(params)), ret(ret) {
        for(auto p : params) {
            arguments.push_back(p);
        }
        this->arguments.push_back(ret);
    };

    Term * substitute(Term * var, Term * term) override;
    std::string toString() override;

    std::vector<Term *> params;
    Term * ret;
    bool operator==(const Term& other) const override;
    bool operator!=(const Term& other) const override;
};

