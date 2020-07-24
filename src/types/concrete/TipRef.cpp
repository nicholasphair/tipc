#include "TipRef.h"
#include <sstream>

TipRef::TipRef(std::shared_ptr<TipType> of): of(of) {
    // TODO: Not yet implemented
    //arguments.push_back(of.get());
}

std::string TipRef::toString() {
    std::stringstream stream;
    stream << "&" << of->toString();
    return stream.str();
}

bool TipRef::operator==(const TipType &other) const {
    if(auto t = dynamic_cast<const TipRef *>(&other)) {
        return *of == *(t->of);
    }
    return false;
}

bool TipRef::operator!=(const TipType &other) const {
    return !(*this == other);
}
