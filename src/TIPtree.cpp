#pragma once
#include "TIPtreeVisitor.h"

void TIPtree::NumberExpr::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_numberExpr(this);
}

void TIPtree::VariableExpr::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_variableExpr(this);
}

void TIPtree::BinaryExpr::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_binaryExpr(this);
}

void TIPtree::FunAppExpr::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_funAppExpr(this);
}

void TIPtree::InputExpr::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_inputExpr(this);
}

void TIPtree::AllocExpr::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_allocExpr(this);
}

void TIPtree::RefExpr::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_refExpr(this);
}

void TIPtree::DeRefExpr::accept(TIPtreeVisitor const * visitor) const {
visitor->visit_deRefExpr(this);
}

void TIPtree::NullExpr::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_nullExpr(this);
}

void TIPtree::FieldExpr::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_fieldExpr(this);
}

void TIPtree::RecordExpr::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_recordExpr(this);
}

void TIPtree::AccessExpr::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_accessExpr(this);
}

void TIPtree::DeclStmt::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_declStmt(this);
}

void TIPtree::BlockStmt::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_blockStmt(this);
}

void TIPtree::AssignStmt::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_assignStmt(this);
}

void TIPtree::WhileStmt::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_whileStmt(this);
}

void TIPtree::IfStmt::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_ifStmt(this);
}

void TIPtree::OutputStmt::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_outputStmt(this);
}

void TIPtree::ErrorStmt::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_errorStmt(this);
}

void TIPtree::ReturnStmt::accept(TIPtreeVisitor const * visitor) const  {
    visitor->visit_returnStmt(this);
}

void TIPtree::Function::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_function(this);
}

void TIPtree::Program::accept(TIPtreeVisitor const * visitor) const {
    visitor->visit_program(this);
}
