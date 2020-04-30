#include "mu.hpp"

std::set<Term *> Mu::free_variables() {
    auto s1 = t->free_variables();
    s1.erase(v);
    return s1;
}

//std::string Mu::toString() {
//    // TODO: make this meaningful.
//    return "\u03bc$v.$t";
//}

