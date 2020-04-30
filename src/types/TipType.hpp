#ifndef TIPC_TIPTYPE_H
#define TIPC_TIPTYPE_H

#include "../TIPtree.h"

class TipType {
public:
    //TipType() = delete;
    virtual std::string toString() = 0;
};


#endif //TIPC_TIPTYPE_H
