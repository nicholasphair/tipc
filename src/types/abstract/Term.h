#pragma once

#include <set>
#include <memory>

class Term {
public:
    virtual std::set<std::shared_ptr<Term>> free_variables() = 0;
    virtual std::shared_ptr<Term> substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) = 0 ;
    virtual std::string toString() = 0;
    virtual bool operator==(const Term& other) const = 0;
    virtual bool operator!=(const Term& other) const = 0;
};

