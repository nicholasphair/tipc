#include "tip_var.hpp"

TipVar::TipVar(TIPtree::Node * node) {
    this->node = node;
}

TipVar::TipVar() {
    assert(0);
}

std::string TipVar::toString() {
    std::string p = this->node->print();
    return "\u03B1<" + p + ">";
}

bool TipVar::is_concrete() {
    return true;
}

