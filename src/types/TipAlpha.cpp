#include "TipAlpha.hpp"
#include "Var.hpp"
#include <sstream>

std::string TipAlpha::toString() {
    std::stringstream stream;
    stream << "\u03B1";
    //if(x.has_value()) {
    //    stream << "<" << x.>";
    //}
    return stream.str();
}

bool TipAlpha::operator==(const Term &other) const {
    if(auto t = dynamic_cast<const TipAlpha *>(&other)) {
        return x == t->x;
    }
    return false;
}

bool TipAlpha::operator!=(const Term &other) const {
    return !(*this == other);
}
