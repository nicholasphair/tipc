#include "tip_alpha.hpp"
#include "var.hpp"
#include "assert.h"

TipAlpha::TipAlpha() {
    assert(0);
}

TipAlpha::TipAlpha(std::any x) {
    this->x = x;
}

std::string TipAlpha::toString() {
    // TODO: Make Meaning.
    return "\u03B1<$x>";
}

bool TipAlpha::is_concrete() {
    return true;
}


