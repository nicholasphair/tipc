#pragma once

#include <set>
#include <memory>

class Term {
public:
    virtual std::string toString() = 0;
    virtual bool operator==(const Term& other) const = 0;
    virtual bool operator!=(const Term& other) const = 0;
};

