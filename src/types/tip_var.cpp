#include "tip_var.hpp"

TipVar::TipVar(TIPtree::Node * node) {
    this->node = node;
}

TipVar::TipVar() {
    assert(0);
}

std::string TipVar::toString() {
    std::string str;
    str += "[[";
    str += this->node->print();
    str += "]]";
    return str;
}

bool TipVar::is_concrete() {
    return true;
}

