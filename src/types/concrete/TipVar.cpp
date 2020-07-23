#include "TipVar.h"
#include <sstream>
#include <iostream>

TipVar::TipVar(AST::Node * node): node(node) {};

std::string TipVar::toString() {
    std::stringstream stream;
    // TODO: Overload output
    //stream << "[[" << node->print() << "]]";
    return stream.str();
}

bool TipVar::operator==(const Term &other) const {
    if(auto t = dynamic_cast<TipVar const *>(&other)) {
        return node == t->node;
    }
    return false;
}

bool TipVar::operator!=(const Term &other) const {
    return !(*this == other);
}
