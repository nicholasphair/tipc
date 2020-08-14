#pragma once

#include "ASTVisitor.h"
#include "ConstraintHandler.h"
#include "SymbolTable.h"
#include "TipType.h"
#include <memory>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include "TypeConstraintVisitor.h"
#include "TypeConstraint.h"

/*! \class TypeConstraintVisitor
 *  \brief Visitor generates type constraints and processes them.
 *
 * This visitor performs a post-order visit of the program AST.  It
 * constructs type constraints for each node that requires a type judgement.
 * The constraints are processed by a function that is passed as a parameter
 * to the visitor.  This provides flexibility in using the visitor - it
 * can simply record the constraints or it can solve them on the fly.
 */
class TypeConstraintCollectVisitor: public TypeConstraintVisitor {
public:
    explicit TypeConstraintCollectVisitor(SymbolTable *pTable);
    std::vector<TypeConstraint>& getCollectedConstraints();
private:
    static std::unique_ptr<ConstraintHandler> buildConstraintHandler();
};

