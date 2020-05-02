#ifndef TIPC_ASTHELPER_H
#define TIPC_ASTHELPER_H

#include "UniqueIdentifiersVisitor.hpp"
#include <sstream>
#include <TIPLexer.h>
#include <TIPParser.h>
#include "antlr4-runtime.h"
#include "../../TIPtreeBuild.h"
#include <istream>

class ASTHelper {
public:
    static std::unique_ptr<TIPtree::Program> build_ast(std::istream &stream);

};


#endif //TIPC_ASTHELPER_H
