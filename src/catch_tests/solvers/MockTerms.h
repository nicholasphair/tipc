#ifndef TIPC_MOCKTERMS_H
#define TIPC_MOCKTERMS_H
#include "cons.hpp"
#include "mu.hpp"
#include "term.hpp"
#include "var.hpp"

/**
 * Lightweight Mock objects for testing our abstract classes.
 */

class TestTerm: public Term { ;
    Term * substitute(Term * var, Term * term) override {return nullptr;};
    bool is_concrete() override { return true; }
    std::set<Term * > free_variables() override { std::set<Term *> s; return s;}
};

class TestCons: public Cons {
    Term * substitute(Term * var, Term * term) override {return nullptr;};
    bool is_concrete() override { return true; }
};

class TestVar: public Var {
    bool is_concrete() override { return true; }
};

class TestMu: public Mu {
    Term * substitute(Term * var, Term * term) override {return nullptr;};
    bool is_concrete() override { return true; }
};


#endif //TIPC_MOCKTERMS_H
