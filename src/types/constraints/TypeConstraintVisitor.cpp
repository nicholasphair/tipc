#include "TypeConstraintVisitor.h"
#include <iostream>
#include "TipVar.h"
#include "TipFunction.h"
#include "TipAlpha.h"
#include "TipRef.h"
#include "TipInt.h"

TypeConstraintVisitor::TypeConstraintVisitor(SymbolTable table): symbolTable(table) {};

std::vector<TypeConstraint> TypeConstraintVisitor::get_constraints() {
    return constraints;
}

// TODO: Revisit w/ stack logic...
void TypeConstraintVisitor::endVisit(AST::Program * element) {
    auto main = element->findFunctionByName(ENTRYPOINT_NAME);
    if(main == nullptr) {
        assert(false);
    }

    for(auto formal : main->getFormals()) {
        auto name = symbolTable.getLocal(formal->getName(), main->getDecl());
        TipVar * var = new TipVar(name);
        TipInt * tipInt = new TipInt();
        TypeConstraint typeConstraint(var, tipInt);
        constraints.push_back(typeConstraint);
    }

    auto returnStatement = main->getStmts().back();
    TipVar * var = new TipVar(returnStatement);
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(var, tipInt);
    constraints.push_back(constraint);
}

// Function declaration
void TypeConstraintVisitor::endVisit(AST::Function * element) {
    std::vector<Term *> args;
    for(auto &formal : element->getFormals()) {
        auto formalDecl = symbolTable.getLocal(formal->getName(), element->getDecl());
        TipVar * var = new TipVar(formalDecl);
        args.push_back(var);
    }
    TipVar * ret = new TipVar(element->getStmts().back());
    TipFunction * tipFunction = new TipFunction(args, ret);

    TipVar * tipVar = new TipVar(element->getDecl());

    TypeConstraint constraint(tipVar, tipFunction);
    constraints.push_back(constraint);
}

// NOTE: DONE.
void TypeConstraintVisitor::endVisit(AST::NumberExpr * element) {
    TipVar * tipVar = new TipVar(element);
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);
}

// NOTE: DONE.
void TypeConstraintVisitor::endVisit(AST::VariableExpr * element) {
    visitResults.push(element->getName());
    //  Leaf node that is a variable. We cannot make any claim about the type of this expression.
}

// TODO: i think I need to use a stack.. When its a leaf and a decl push it
void TypeConstraintVisitor::endVisit(AST::BinaryExpr  * element) {
    TipVar * e1 = safeTipVarGenerate(element->getLeft());
    TipVar * e2 = safeTipVarGenerate(element->getRight());
    TipVar * e1_eq_e2 = safeTipVarGenerate(element);
    TipInt * tipInt = new TipInt();

    TypeConstraint constraint1(e1, e2);
    TypeConstraint constraint2(e1, e1_eq_e2);
    TypeConstraint constraint3(e1, tipInt);
    TypeConstraint constraint4(e2, e1_eq_e2);
    TypeConstraint constraint5(e2, tipInt);
    TypeConstraint constraint6(e1_eq_e2, tipInt);

    if(element->getOp() == "==") {
        constraints.push_back(constraint1);
        constraints.push_back(constraint6);
    } else {
        constraints.push_back(constraint1);
        constraints.push_back(constraint2);
        constraints.push_back(constraint3);
        constraints.push_back(constraint4);
        constraints.push_back(constraint5);
        constraints.push_back(constraint6);
    }

    element->getLeft()->accept(this);
    element->getRight()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::InputExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);
}

void TypeConstraintVisitor::endVisit(AST::FunAppExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);

    element->getFunction()->accept(this);
    std::vector<Term *> actuals;
    for (auto  &arg : element->getActuals()) {
        arg->accept(this);
        actuals.push_back(safeTipVarGenerate(arg));
    }

    TipVar * application = safeTipVarGenerate(element->getFunction());
    TipFunction * f = new TipFunction(actuals, application);
    TypeConstraint constraint(tipVar, f);
    constraints.push_back(constraint);
}

void TypeConstraintVisitor::endVisit(AST::AllocExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);
    TipVar * tipVar2 = safeTipVarGenerate(element->getInitializer());
    TipRef * tipRef = new TipRef(tipVar2);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);

    element->getInitializer()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::RefExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);
    TipVar * tipVar2 = safeTipVarGenerate(&canonicals.at(element->getVar()));
    TipRef * tipRef = new TipRef(tipVar2);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);
}

void TypeConstraintVisitor::endVisit(AST::DeRefExpr * element) {
    TipVar * tipVar = safeTipVarGenerate(element->getPtr());
    TipVar * tipVar2 = safeTipVarGenerate(element);
    TipRef * tipRef = new TipRef(tipVar2);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);

    element->getPtr()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::NullExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);
    TipAlpha * tipAlpha = new TipAlpha("");
    TipRef * tipRef = new TipRef(tipAlpha);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);
}

void TypeConstraintVisitor::endVisit(AST::DeclStmt  * element) {
    // Variable Declarations make no constraints.
}

void TypeConstraintVisitor::endVisit(AST::AssignStmt  * element) {
    auto lhs = element->getLHS();
    auto rhs = element->getRHS();

    if(auto l = dynamic_cast<AST::DeRefExpr *>(lhs)) {
        TipVar * lvar = safeTipVarGenerate(l->getPtr());
        TipVar * rvar = safeTipVarGenerate(element->getRHS());
        TipRef * rref = new TipRef(rvar);
        TypeConstraint constraint(lvar, rref);
        constraints.push_back(constraint);
    } else {
        TipVar * lvar = safeTipVarGenerate(element->getLHS());
        TipVar * rvar = safeTipVarGenerate(element->getRHS());
        TypeConstraint constraint(lvar, rvar);
        constraints.push_back(constraint);

        //element->LHS->accept(this);
    }
    element->getRHS()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::WhileStmt  * element) {
    TipVar * tipVar = safeTipVarGenerate(element->getCondition());
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    element->getCondition()->accept(this);
    element->getBody()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::IfStmt  * element) {
    TipVar * tipVar = safeTipVarGenerate(element->getCondition());
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    element->getCondition()->accept(this);
    element->getCondition()->accept(this);

    if (element->getElse() != nullptr) {
        element->getElse()->accept(this);
    }
}

void TypeConstraintVisitor::endVisit(AST::OutputStmt  * element) {
    TipVar * tipVar = safeTipVarGenerate(element->getArg());
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    element->getArg()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::ReturnStmt  * element) {
    // We cannot say anything about a return stmt.
    element->getArg()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::FieldExpr  * element) {
    element->getInitializer()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::RecordExpr  * element) {
    for (auto  &field : element->getFields()) {
        field->accept(this);
    }
}

void TypeConstraintVisitor::endVisit(AST::AccessExpr  * element) {
    element->getRecord()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::ErrorStmt  * element) {
    element->getArg()->accept(this);
}

void TypeConstraintVisitor::endVisit(AST::BlockStmt  * element) {
    for (auto  &s : element->getStmts()) {
        s->accept(this);
    }
}

// RECALL, I've canonicalized all of our identifiers (nodes?) I want to use
// the canonical represenations. Is my canonicalization just to get around my failures
// to implement the a proper comarrison operators? Or does the canonicalization go deeper???
TipVar * TypeConstraintVisitor::safeTipVarGenerate(std::string name) {
    return new TipVar(&canonicals.at(name));
}

TipVar * TypeConstraintVisitor::safeTipVarGenerate(AST::Node * node) {
    if(canonicals.count(node->print()) != 0) {
        return new TipVar(&canonicals.at(node->print()));
    }
    return new TipVar(node);
}
