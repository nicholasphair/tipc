#include "TypeConstraintVisitor.h"
#include <iostream>
#include "TipVar.h"
#include "TipFunction.h"
#include "TipAlpha.h"
#include "TipRef.h"
#include "TipInt.h"
#include <memory>

/**
 * Any given Term can be shared by multiple constraints. As such, we use a shared_ptr.
 */
TypeConstraintVisitor::TypeConstraintVisitor(SymbolTable table): symbolTable(table) {};

std::vector<TypeConstraint> TypeConstraintVisitor::get_constraints() {
    return constraints;
}

void TypeConstraintVisitor::endVisit(AST::Program * element) {
    auto main = element->findFunctionByName(ENTRYPOINT_NAME);
    //if(main == nullptr) {
    //    assert(false);
    //}

    //for(auto formal : main->getFormals()) {
    //    auto name = symbolTable.getLocal(formal->getName(), main->getDecl());
    //    auto var = std::make_shared<TipVar>(name);
    //    auto tipInt = std::make_shared<TipInt>();
    //    TypeConstraint typeConstraint(var, tipInt);
    //    constraints.push_back(typeConstraint);
    //}

    //auto returnStatement = main->getStmts().back();
    //auto var = std::make_shared<TipVar>(returnStatement);
    //auto tipInt = std::make_shared<TipInt>();
    //TypeConstraint constraint(var, tipInt);
    //constraints.push_back(constraint);
}


bool TypeConstraintVisitor::visit(AST::Function * element) {
    scope.push(element->getDecl());
    return true;
}

// Function declaration
void TypeConstraintVisitor::endVisit(AST::Function * element) {
    //std::shared_ptr<TipInt> node = std::make_shared<TipVar>(element);
    auto node = std::make_shared<TipVar>(element);

    // function name, formal, declars, stmts
    auto ret = visitResults.top();
    for(auto &_ : element->getStmts()) {
        visitResults.pop();
    }

    for(auto &_ : element->getDeclarations()) {
        visitResults.pop();
    }

    std::vector<std::shared_ptr<TipType>> formals;
    for(auto &_ : element->getFormals()) {
        formals.push_back(visitResults.top());
        visitResults.pop();
    }

    auto tipFunction = std::make_shared<TipFunction>(formals, ret);
    TypeConstraint constraint(visitResults.top(), tipFunction);
    visitResults.pop();
    constraints.push_back(constraint);

    visitResults.push(node);
    scope.pop();
}

void TypeConstraintVisitor::endVisit(AST::NumberExpr * element) {
    auto node = std::make_shared<TipVar>(element);
    TypeConstraint constraint(node, std::make_shared<TipInt>());
    constraints.push_back(constraint);
    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::VariableExpr * element) {
    auto canonical = symbolTable.getLocal(element->getName(), scope.top());
    visitResults.push(std::make_shared<TipVar>(canonical));
}

// TODO: i think I need to use a stack.. When its a leaf and a decl push it
void TypeConstraintVisitor::endVisit(AST::BinaryExpr  * element) {
    auto node = std::make_shared<TipVar>(element);

    // left is visited then right is visited.
    auto e2 = visitResults.top();
    visitResults.pop();
    auto e1 = visitResults.top();
    visitResults.pop();

    auto tipInt = std::make_shared<TipInt>();

    TypeConstraint constraint1(e1, e2);
    TypeConstraint constraint2(e1, node);
    TypeConstraint constraint3(e1, tipInt);
    TypeConstraint constraint4(e2, node);
    TypeConstraint constraint5(e2, tipInt);
    TypeConstraint constraint6(node, tipInt);

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

    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::InputExpr * element) {
    auto node = std::make_shared<TipVar>(element);
    TypeConstraint constraint(node, std::make_shared<TipInt>());
    constraints.push_back(constraint);

    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::FunAppExpr  * element) {
    auto node = std::make_shared<TipVar>(element);

    std::vector<std::shared_ptr<TipType>> actuals;
    for(auto _ : element->getActuals()) {
        actuals.push_back(visitResults.top());
        visitResults.pop();
    }

    auto function = std::make_shared<TipFunction>(actuals, node);
    auto application = visitResults.top();
    visitResults.pop();
    TypeConstraint constraint(application, function);
    constraints.push_back(constraint);
    visitResults.push(node);
}

// DONE.
void TypeConstraintVisitor::endVisit(AST::AllocExpr * element) {
    auto node = std::make_shared<TipVar>(element);

    auto initializer = visitResults.top();
    visitResults.pop();
    auto tipRef = std::make_shared<TipRef>(initializer);
    TypeConstraint constraint(node, tipRef);
    constraints.push_back(constraint);
    visitResults.push(node);
}


void TypeConstraintVisitor::endVisit(AST::RefExpr * element) {
    auto node = std::make_shared<TipVar>(element);

    auto var = visitResults.top();
    visitResults.pop();
    auto tipRef = std::make_shared<TipRef>(var);
    TypeConstraint constraint(node, tipRef);
    constraints.push_back(constraint);

    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::DeRefExpr * element) {
    auto node = std::make_shared<TipVar>(element);
    auto tipRef = std::make_shared<TipRef>(node);

    auto dereferenced = visitResults.top();
    visitResults.pop();

    TypeConstraint constraint(dereferenced, tipRef);
    constraints.push_back(constraint);

    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::NullExpr * element) {
    auto node = std::make_shared<TipVar>(element);

    auto tipAlpha = std::make_shared<TipAlpha>("");
    auto tipRef = std::make_shared<TipRef>(tipAlpha);

    TypeConstraint constraint(node, tipRef);
    constraints.push_back(constraint);
    visitResults.push(node);
}

// Variable Declarations make no constraints.
void TypeConstraintVisitor::endVisit(AST::DeclStmt * element) {
    auto node = std::make_shared<TipVar>(element);
    for(auto &_ : element->getVars()) {
        visitResults.pop();
    }
    visitResults.push(node);
}

// No need to to a symbol table lookup. These are the canonical forms.
void TypeConstraintVisitor::endVisit(AST::DeclNode * element) {
    auto node = std::make_shared<TipVar>(element);
    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::AssignStmt  * element) {
    auto node = std::make_shared<TipVar>(element);

    auto rhs = visitResults.top();
    visitResults.pop();
    auto lhs = visitResults.top();
    visitResults.pop();

    TypeConstraint constraint(lhs, rhs);
    constraints.push_back(constraint);

    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::WhileStmt * element) {
    auto node = std::make_shared<TipVar>(element);

    // Pop off the body.
    visitResults.pop();

    auto condition = visitResults.top();
    visitResults.pop();

    TypeConstraint constraint(condition, std::make_shared<TipInt>());
    constraints.push_back(constraint);

    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::IfStmt * element) {
    auto node = std::make_shared<TipVar>(element);

    // Pop off the statements.
    if (element->getElse() != nullptr) {
        visitResults.pop();
    }
    visitResults.pop();

    auto condition = visitResults.top();
    visitResults.pop();

    TypeConstraint constraint(condition, std::make_shared<TipInt>());
    constraints.push_back(constraint);

    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::OutputStmt * element) {
    auto node = std::make_shared<TipVar>(element);

    auto argument = visitResults.top();
    visitResults.pop();

    auto tipInt = std::make_shared<TipInt>();

    TypeConstraint constraint(argument, tipInt);
    constraints.push_back(constraint);

    visitResults.push(node);
}

void TypeConstraintVisitor::endVisit(AST::ReturnStmt * element) {
    auto var = std::make_shared<TipVar>(element);
    visitResults.pop();  // Pop the arg.
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

