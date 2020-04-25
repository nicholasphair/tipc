#ifndef CONS_HPP
#define CONS_HPP
#include "term.hpp"
#include <set>
#include <vector>

class Cons: public Term {
public:
    std::set<Term *> free_variables() override;
    std::vector<Term *> arguments;
    int arity();
    bool do_match(Term * t);
};

#endif /* CONS_HPP */