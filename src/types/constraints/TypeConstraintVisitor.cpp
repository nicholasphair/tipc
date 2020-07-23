#include "TypeConstraintVisitor.h"
#include <iostream>
#include "TipVar.h"
#include "TipFunction.h"
#include "TipAlpha.h"
#include "TipRef.h"
#include "TipInt.h"
// TODO: Active function variable -- that way I can look up nodes
// TODO: Is there an invariant that at the end of each visit the stack is empty

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
        auto var = std::make_shared<TipVar>(name);
        auto tipInt = std::make_shared<TipInt>();
        TypeConstraint typeConstraint(var, tipInt);
        constraints.push_back(typeConstraint);
    }

    auto returnStatement = main->getStmts().back();
    auto var = std::make_shared<TipVar>(returnStatement);
    auto tipInt = std::make_shared<TipInt>();
    TypeConstraint constraint(var, tipInt);
    constraints.push_back(constraint);
}


bool TypeConstraintVisitor::visit(AST::Function * element) {
    scope.push(element->getDecl());
}

// Function declaration
void TypeConstraintVisitor::endVisit(AST::Function * element) {
    // function name, formal, declars, stmts
    auto ret = visitResults.top();
    for(int i = 0; i < element->getStmts().size(); i++) {
        visitResults.pop();
    }

    for(int i = 0; i < element->getDeclarations().size(); i++) {
        visitResults.pop();
    }

    std::vector<std::shared_ptr<Term>> args;
    for(int i = 0; i < element->getFormals().size(); i++) {
        auto formal = visitResults.top();
        args.push_back(formal);
        visitResults.pop();
    }

    auto tipFunction = std::make_shared<TipFunction>(args, ret);

    TipFunction tipFunction2(args, ret);
    visitResults2.push(tipFunction2);

    auto fn = visitResults.top();
    visitResults.pop();
    TypeConstraint constraint(fn, tipFunction);
    constraints.push_back(constraint);

    auto var = std::make_shared<TipVar>(element);
    visitResults.push(var);
    scope.pop();
}

// NOTE: DONE.
void TypeConstraintVisitor::endVisit(AST::NumberExpr * element) {
    auto tipVar = std::make_shared<TipVar>(element);
    auto tipInt = std::make_shared<TipInt>();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);
    visitResults.push(tipVar);
}

void TypeConstraintVisitor::endVisit(AST::VariableExpr * element) {
    // TODO: I need to be able to get my canonical form...
    auto var = symbolTable.getLocal(element->getName(), scope.top());
    auto tipVar = std::make_shared<TipVar>(var);
    visitResults.push(tipVar);
}

// TODO: i think I need to use a stack.. When its a leaf and a decl push it
void TypeConstraintVisitor::endVisit(AST::BinaryExpr  * element) {
    // left is visited then right is visited.
    auto e1 = visitResults.top();
    visitResults.pop();
    auto e2 = visitResults.top();
    visitResults.pop();

    auto e1_eq_e2 = std::make_shared<TipVar>(element);
    auto tipInt = std::make_shared<TipInt>();

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

    visitResults.push(e1_eq_e2);
}

void TypeConstraintVisitor::endVisit(AST::InputExpr * element) {
    auto tipVar = std::make_shared<TipVar>(element);
    auto tipInt = std::make_shared<TipInt>();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);
    visitResults.push(tipVar);
}

// TODO
void TypeConstraintVisitor::endVisit(AST::FunAppExpr  * element) {
    auto tipVar = std::make_shared<TipVar>(element);

    std::vector<std::shared_ptr<Term>> actuals;
    for(int i = 0; i < element->getActuals().size() - 1; i++) {
        auto actual = visitResults.top();
        actuals.push_back(actual);
        visitResults.pop();
    }

    auto application = visitResults.top();
    visitResults.pop();
    auto function = std::make_shared<TipFunction>(actuals, application);
    TypeConstraint constraint(tipVar, function);
    constraints.push_back(constraint);
    visitResults.push(tipVar);
}

// DONE.
void TypeConstraintVisitor::endVisit(AST::AllocExpr * element) {
    auto tipVar = std::make_shared<TipVar>(element);
    auto tipVar2 = visitResults.top();
    visitResults.pop();
    auto tipRef = std::make_shared<TipRef>(tipVar2);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);
    visitResults.push(tipVar);
}


void TypeConstraintVisitor::endVisit(AST::RefExpr * element) {
    auto tipVar = std::make_shared<TipVar>(element);
    auto tipVar2 = visitResults.top();
    visitResults.pop();
    auto tipRef = std::make_shared<TipRef>(tipVar2);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);
    visitResults.push(tipVar2);
}

void TypeConstraintVisitor::endVisit(AST::DeRefExpr * element) {
    auto tipVar = visitResults.top();
    visitResults.pop();
    auto tipVar2 = std::make_shared<TipVar>(element);
    auto tipRef = std::make_shared<TipRef>(tipVar2);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);
    visitResults.push(tipVar2);
}

void TypeConstraintVisitor::endVisit(AST::NullExpr * element) {
    // TODO: nulls need to be cannonicalized somehow.
    auto tipVar = std::make_shared<TipVar>(element);
    auto tipAlpha = std::make_shared<TipAlpha>("");
    auto tipRef = std::make_shared<TipRef>(tipAlpha);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);
    visitResults.push(tipVar);
}

void TypeConstraintVisitor::endVisit(AST::DeclStmt * element) {
    auto tipVar = std::make_shared<TipVar>(element);
    visitResults.push(tipVar);
    // Variable Declarations make no constraints.
}

void TypeConstraintVisitor::endVisit(AST::DeclNode * element) {
    auto tipVar = std::make_shared<TipVar>(element);
    visitResults.push(tipVar);
}

void TypeConstraintVisitor::endVisit(AST::AssignStmt  * element) {
    // visit left then visit right
    auto rhs = visitResults.top();
    visitResults.pop();
    auto lhs = visitResults.top();
    visitResults.pop();

    TypeConstraint constraint(lhs, rhs);
    constraints.push_back(constraint);

    // NOTE: I think this is right..
    auto tipVar = std::make_shared<TipVar>(element);
    visitResults.push(tipVar);
}

void TypeConstraintVisitor::endVisit(AST::WhileStmt * element) {
    // TODO: Confirm that this is the condition.
    auto tipVar = visitResults.top();
    visitResults.pop();
    auto tipInt = std::make_shared<TipInt>();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    auto var = std::make_shared<TipVar>(element);
    visitResults.push(var);
}

void TypeConstraintVisitor::endVisit(AST::IfStmt * element) {
    // TODO: verify this is the condition..
    auto tipVar = visitResults.top();
    visitResults.pop();
    auto tipInt = std::make_shared<TipInt>();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    auto var = std::make_shared<TipVar>(element);
    visitResults.push(var);
}

void TypeConstraintVisitor::endVisit(AST::OutputStmt * element) {
    auto tipVar = visitResults.top();
    visitResults.pop();
    auto tipInt = std::make_shared<TipInt>();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    auto var = std::make_shared<TipVar>(element);
    visitResults.push(var);
}

void TypeConstraintVisitor::endVisit(AST::ReturnStmt * element) {
    auto var = std::make_shared<TipVar>(element);
    visitResults.push(var);
}

void TypeConstraintVisitor::endVisit(AST::FieldExpr  * element) {
    // NOT IMPLEMENTED.
    assert(0);
}

void TypeConstraintVisitor::endVisit(AST::RecordExpr * element) {
    // NOT IMPLEMENTED.
    assert(0);
}

void TypeConstraintVisitor::endVisit(AST::AccessExpr * element) {
    // NOT IMPLEMENTED.
    assert(0);
}

void TypeConstraintVisitor::endVisit(AST::ErrorStmt * element) {
    // TODO
    assert(0);
    auto tipVar = visitResults.top();
    visitResults.pop();
    auto tipInt = std::make_shared<TipInt>();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    auto var = std::make_shared<TipVar>(element);
    visitResults.push(var);
}

void TypeConstraintVisitor::endVisit(AST::BlockStmt * element) {
    // TODO
    assert(0);
}

