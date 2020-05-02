#ifndef TERM_HPP
#define TERM_HPP
#include <set>

class Term {
public:
    virtual std::set<Term * > free_variables() = 0;
    virtual Term * substitute(Term * var, Term * term) = 0 ;
    virtual std::string toString() = 0;
    virtual bool operator==(const Term& other) const = 0;
    virtual bool operator!=(const Term& other) const = 0;
};

#endif /* TERM_HPP */
