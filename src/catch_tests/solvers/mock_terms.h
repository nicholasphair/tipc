#ifndef TIPC_MOCK_TERMS_H
#define TIPC_MOCK_TERMS_H
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
    std::string toString() override {return "mock term";};
};

class TestCons: public Cons {
    Term * substitute(Term * var, Term * term) override {return nullptr;};
    bool is_concrete() override { return true; }
    std::string toString() override {return "mock cons";};
};

class TestVar: public Var {
    bool is_concrete() override { return true; }
    std::string toString() override {return "mock var";};
};

class TestMu: public Mu {
    Term * substitute(Term * var, Term * term) override {return nullptr;};
    bool is_concrete() override { return true; }
    std::string toString() override {return "mock mu";};
};


#endif //TIPC_MOCK_TERMS_H
