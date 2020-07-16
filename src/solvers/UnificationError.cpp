//
// Created by nphair on 4/25/20.
//

#include "UnificationError.h"

UnificationError::UnificationError(const char *msg) {
    this->msg = msg;
}

const char * UnificationError::what() const throw() {
    return msg;
}
