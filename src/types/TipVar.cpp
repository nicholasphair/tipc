#include "TipVar.hpp"
#include <sstream>
#include <iostream>

std::string TipVar::toString() {
    std::stringstream stream;
    stream << "[[" << node->print() << "]]";
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