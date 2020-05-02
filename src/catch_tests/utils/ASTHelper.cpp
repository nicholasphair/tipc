//
// Created by nphair on 5/1/20.
//

#include "utils/ASTHelper.hpp"
#include "UniqueIdentifiersVisitor.hpp"
#include <sstream>
#include <TIPLexer.h>
#include <TIPParser.h>
#include "antlr4-runtime.h"
#include "../../TIPtreeBuild.h"

std::unique_ptr<TIPtree::Program> ASTHelper::build_ast(std::istream &stream) {
    antlr4::ANTLRInputStream input(stream);
    TIPLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    TIPParser parser(&tokens);
    TIPParser::ProgramContext *tree = parser.program();
    TIPtreeBuild tb(&parser);
    return tb.build(tree);
}
