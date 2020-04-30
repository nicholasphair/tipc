#include "TIPtreeSimpleVisitor.h"
#include <iostream>

void TIPtreeSimpleVisitor::visit_program(TIPtree::Program const *element) const {
    std::cout << "visit_program" << std::endl;
    for (auto &fn : element->FUNCTIONS) {
        fn->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_function(TIPtree::Function const * element) const {
    std::cout << "visit_function" << std::endl;
    for (auto const &decl : element->DECLS) {
        decl->accept(this);
    }

    for (auto const &stmt : element->BODY) {
        stmt->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_numberExpr(TIPtree::NumberExpr const * element) const {
    std::cout << "visit_numberExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_variableExpr (TIPtree::VariableExpr const * element) const {
    std::cout << "visit_variableExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_binaryExpr(TIPtree::BinaryExpr const * element) const {
    std::cout << "visit_binaryExpr" << std::endl;
    element->LHS->accept(this);
    element->RHS->accept(this);
}

void TIPtreeSimpleVisitor::visit_inputExpr(TIPtree::InputExpr const * element) const {
    std::cout << "visit_inputExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_funAppExpr (TIPtree::FunAppExpr const * element) const {
    std::cout << "visit_funAppExpr" << std::endl;
    element->FUN->accept(this);
    for (auto const &arg : element->ACTUALS) {
        arg->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_allocExpr(TIPtree::AllocExpr const * element) const {
    std::cout << "visit_allocExpr" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_refExpr (TIPtree::RefExpr const * element) const {
    std::cout << "visit_refExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_deRefExpr (TIPtree::DeRefExpr const * element) const {
    std::cout << "visit_deRefExpr" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_nullExpr(TIPtree::NullExpr const * element) const {
    std::cout << "visit_nullExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_declStmt(TIPtree::DeclStmt const * element) const {
    std::cout << "visit_declStmt" << std::endl;
}

void TIPtreeSimpleVisitor::visit_assignStmt (TIPtree::AssignStmt const * element) const {
    std::cout << "visit_assignStmt" << std::endl;
    element->LHS->print();
    element->RHS->print();
}

void TIPtreeSimpleVisitor::visit_whileStmt(TIPtree::WhileStmt const * element) const {
    std::cout << "visit_whileStmt" << std::endl;
    element->COND->accept(this);
    element->BODY->print();
}

void TIPtreeSimpleVisitor::visit_ifStmt(TIPtree::IfStmt const * element) const {
    std::cout << "visit_ifStmt" << std::endl;
    element->COND->print();
    element->THEN->print();

    if (element->ELSE != nullptr) {
        element->ELSE->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_outputStmt(TIPtree::OutputStmt const * element) const {
    std::cout << "visit_outputStmt" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_returnStmt(TIPtree::ReturnStmt const * element) const {
    std::cout << "visit_returnStmt" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_fieldExpr(TIPtree::FieldExpr const * element) const {
    std::cout << "visit_fieldExp" << std::endl;
    element->INIT->accept(this);
}

void TIPtreeSimpleVisitor::visit_recordExpr(TIPtree::RecordExpr const * element) const {
    std::cout << "visit_recordEpr" << std::endl;
    for (auto const &field : element->FIELDS) {
        field->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_accessExpr(TIPtree::AccessExpr const * element) const {
    std::cout << "visit_accessExp" << std::endl;
    element->RECORD->accept(this);
}

void TIPtreeSimpleVisitor::visit_errorStmt(TIPtree::ErrorStmt const * element) const {
    std::cout << "visit_errorStmt" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_blockStmt(TIPtree::BlockStmt const * element) const {
    std::cout << "visit_blockStm" << std::endl;
    for (auto const &s : element->STMTS) {
        s->accept(this);
    }
}
