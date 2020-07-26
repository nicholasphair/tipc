#pragma once


#include <string>
#include <PrettyPrinter.h>
#include <types/concrete/TipType.h>

/**
 * Returns human-readable string representations of nodes and types.
 */
class FriendlyNodeStringifier {
public:
    static std::string stringify(AST::Node * node);
    static std::string stringify(TipType * tipType);
};

