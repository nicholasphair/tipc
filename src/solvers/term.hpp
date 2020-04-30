#ifndef TERM_HPP
#define TERM_HPP
#include <set>

class Term {
public:
    // TODO: must make sure free_vars and vars are, well, vars.
    virtual std::set<Term * > free_variables() = 0;
    virtual Term * substitute(Term * var, Term * term) = 0 ;
    virtual bool is_concrete() = 0;
    virtual std::string toString();
};

std::string Term::toString() {
    return "unimplemented";
}

#endif /* TERM_HPP */
