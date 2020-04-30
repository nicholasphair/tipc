#pragma once
#include "TIPtreeVisitor.h"

void TIPtree::NumberExpr::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_numberExpr(this);
}

void TIPtree::VariableExpr::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_variableExpr(this);
}

void TIPtree::BinaryExpr::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_binaryExpr(this);
}

void TIPtree::FunAppExpr::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_funAppExpr(this);
}

void TIPtree::InputExpr::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_inputExpr(this);
}

void TIPtree::AllocExpr::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_allocExpr(this);
}

void TIPtree::RefExpr::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_refExpr(this);
}

void TIPtree::DeRefExpr::accept(TIPtreeVisitor  * visitor)  {
visitor->visit_deRefExpr(this);
}

void TIPtree::NullExpr::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_nullExpr(this);
}

void TIPtree::FieldExpr::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_fieldExpr(this);
}

void TIPtree::RecordExpr::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_recordExpr(this);
}

void TIPtree::AccessExpr::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_accessExpr(this);
}

void TIPtree::DeclStmt::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_declStmt(this);
}

void TIPtree::BlockStmt::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_blockStmt(this);
}

void TIPtree::AssignStmt::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_assignStmt(this);
}

void TIPtree::WhileStmt::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_whileStmt(this);
}

void TIPtree::IfStmt::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_ifStmt(this);
}

void TIPtree::OutputStmt::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_outputStmt(this);
}

void TIPtree::ErrorStmt::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_errorStmt(this);
}

void TIPtree::ReturnStmt::accept(TIPtreeVisitor  * visitor)   {
    visitor->visit_returnStmt(this);
}

void TIPtree::Function::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_function(this);
}

void TIPtree::Program::accept(TIPtreeVisitor  * visitor)  {
    visitor->visit_program(this);
}
