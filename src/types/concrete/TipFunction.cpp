#include "TipFunction.h"
#include <sstream>

TipFunction::TipFunction(std::vector<std::shared_ptr<TipType>> params, std::shared_ptr<TipType> ret):
  params(std::move(params)), ret(std::move(ret)) { };

int TipFunction::arity() {
    // +1 for the return type.
    return arguments.size() + 1;
}

std::string TipFunction::toString() {
    std::stringstream fmt;
    fmt << "(";
    int i = 0;
    for(auto&& param : params) {
        fmt << param->toString() << (++i == params.size() ? "" : ",");
    }
    fmt << ") -> " << ret->toString();
    return fmt.str();
}

bool TipFunction::operator==(const TipType &other) const {
    if(auto tipFunction = dynamic_cast<const TipFunction *>(&other)) {
        if(arguments.size() != tipFunction->arguments.size()) {
            return false;
        }

        for(int i = 0; i < arguments.size(); i++) {
            if(*(arguments.at(i)) != *(tipFunction->arguments.at(i))) {
                return false;
            }
        }

        return *ret == *(tipFunction->ret);
    }
    return false;
}

bool TipFunction::operator!=(const TipType &other) const {
    return !(*this == other);
}
