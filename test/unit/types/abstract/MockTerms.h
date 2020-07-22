#pragma once

#include "types/abstract/Cons.h"
#include "types/abstract/Mu.h"
#include "types/abstract/Term.h"
#include "Var.h"
#include <iostream>

/**
 * Lightweight Mock objects for testing our abstract classes.
 */

class TestTerm: public Term { ;
    std::shared_ptr<Term> substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) override {
        return nullptr;
    };

    std::set<std::shared_ptr<Term>> free_variables() override {
        std::set<std::shared_ptr<Term>> s;
        return s;
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
    std::shared_ptr<Term> substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) override {
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
    std::shared_ptr<Term> substitute(std::shared_ptr<Term> var, std::shared_ptr<Term> term) override {
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


