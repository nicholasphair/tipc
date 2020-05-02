#ifndef MU_HPP
#define MU_HPP
#include "Term.hpp"
#include "Var.hpp"
#include <string>

class Mu: public Term {

public:
    Var * v;
    Term * t;

    std::set<Term *> free_variables() override;
    //std::string toString();
};

#endif /* MU_HPP */
