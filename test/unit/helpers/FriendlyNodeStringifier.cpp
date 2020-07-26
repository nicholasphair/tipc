#include "FriendlyNodeStringifier.h"
#include <types/concrete/TipInt.h>
#include <sstream>
#include <types/concrete/TipRef.h>
#include <types/concrete/TipFunction.h>
#include <types/concrete/TipVar.h>
#include <types/concrete/TipAlpha.h>
#include "PrettyPrinter.h"


std::string FriendlyNodeStringifier::stringify(AST::Node *node) {
    std::stringstream stream;
    PrettyPrinter prettyPrinter(stream, ' ', 2);
    prettyPrinter.print2(node, stream, ' ', 2);
    return stream.str();
}

std::string FriendlyNodeStringifier::stringify(TipType *tipType) {
    std::stringstream stream;
    if(auto n = dynamic_cast<TipInt *>(tipType)) {
        stream << *n;
    } else if(auto n = dynamic_cast<TipRef *>(tipType)) {
        stream << "&" << stringify(n->of.get());
    } else if(auto n = dynamic_cast<TipFunction *>(tipType)) {
        stream << "(";
        bool first = true;
        std::stringstream params;
        for(auto &param : n->params) {
            if(first) {
                params << stringify(param.get());
                first = false;
                continue;
            }
            params << ", " << stringify(param.get());
        }
        stream << params.str() << ") -> " << stringify(n->ret.get());
    } else if(auto n = dynamic_cast<TipVar *>(tipType)) {
        stream << "[[" << stringify(n->node) << "]]";
    } else if(auto n = dynamic_cast<TipAlpha *>(tipType)) {
        stream << "\u03B1";
    } else {
        assert(0);
    }

    return stream.str();
}
