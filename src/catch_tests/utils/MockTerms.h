#ifndef TIPC_MOCKTERMS_H
#define TIPC_MOCKTERMS_H
#include "Cons.hpp"
#include "Mu.hpp"
#include "Term.hpp"
#include "Var.hpp"
#include <iostream>

/**
 * Lightweight Mock objects for testing our abstract classes.
 */

class TestTerm: public Term { ;
    Term * substitute(Term * var, Term * term) override {
        return nullptr;
    };

    std::set<Term * > free_variables() override {
        std::set<Term *> s; return s;
    }

    std::string toString() override {
        return "mock term";
    };

    bool operator==(const Term& other) const override {
        return true;
    };

    bool operator!=(const Term& other) const override {
        return !(*this == other);
    };
};

class TestCons: public Cons {
    Term * substitute(Term * var, Term * term) override {
        return nullptr;
    };

    std::string toString() override {
        return "mock cons";
    };

    bool operator==(const Term& other) const override {
        std::cout<<"ncons comp"<< std::endl;
        return true;
    };

    bool operator!=(const Term& other) const override {
        return !(*this == other);
    };
};

class TestNCons: public TestCons {
public:
    TestNCons() = delete;
    TestNCons(int arity) : _arity(arity) { }
    int arity() override {
        return _arity;
    }

    int _arity;
};

class TestVar: public Var {
    std::string toString() override {
        return "mock var";
    };

    bool operator==(const Term& other) const override {
        return true;
    };

    bool operator!=(const Term& other) const override {
        return !(*this == other);
    };
};

class TestMu: public Mu {
    Term * substitute(Term * var, Term * term) override {
        return nullptr;
    };

    std::string toString() override {
        return "mock mu";
    };

    bool operator==(const Term& other) const override {
        return true;
    };

    bool operator!=(const Term& other) const override {
        return !(*this == other);
    };
};


#endif //TIPC_MOCKTERMS_H
