#pragma once

#include "../../SymbolTable.h"
#include "ASTVisitor.h"
#include "TipVar.h"
#include "TypeConstraint.h"
#include <stack>
#include <vector>
#include <string>

static const char *const ENTRYPOINT_NAME = "main";

class TypeConstraintVisitor: public ASTVisitor {
public:
    TypeConstraintVisitor() = delete;
    TypeConstraintVisitor(SymbolTable table);

    virtual void endVisit(AST::Program * element) override;
    virtual bool visit(AST::Function * element) override;
    virtual void endVisit(AST::Function * element) override;
    virtual void endVisit(AST::NumberExpr * element) override;
    virtual void endVisit(AST::VariableExpr * element) override;
    virtual void endVisit(AST::BinaryExpr * element) override;
    virtual void endVisit(AST::InputExpr * element) override;
    virtual void endVisit(AST::FunAppExpr * element) override;
    virtual void endVisit(AST::AllocExpr * element) override;
    virtual void endVisit(AST::RefExpr * element) override;
    virtual void endVisit(AST::DeRefExpr * element) override;
    virtual void endVisit(AST::NullExpr * element) override;
    virtual void endVisit(AST::FieldExpr * element) override;
    virtual void endVisit(AST::RecordExpr * element) override;
    virtual void endVisit(AST::AccessExpr * element) override;
    virtual void endVisit(AST::DeclNode * element) override;
    virtual void endVisit(AST::DeclStmt * element) override;
    virtual void endVisit(AST::AssignStmt * element) override;
    virtual void endVisit(AST::WhileStmt * element) override;
    virtual void endVisit(AST::IfStmt * element) override;
    virtual void endVisit(AST::OutputStmt * element) override;
    virtual void endVisit(AST::ReturnStmt * element) override;
    virtual void endVisit(AST::ErrorStmt * element) override;
    virtual void endVisit(AST::BlockStmt * element) override;

    std::vector<TypeConstraint> get_constraints();
private:
    std::vector<TypeConstraint> constraints;
    SymbolTable symbolTable;
    std::stack<std::shared_ptr<Term>> visitResults;
    std::stack<TipType> visitResults2;
    std::stack<AST::DeclNode *> scope;
};

