#include "Mu.h"
#include <sstream>

std::set<std::shared_ptr<Term>> Mu::free_variables() {
    auto s1 = t->free_variables();
    s1.erase(v);
    return s1;
}

std::string Mu::toString() {
    std::stringstream s;
    s << "\u03bc" << v->toString() << "." <<  t->toString();
    return s.str();
}

