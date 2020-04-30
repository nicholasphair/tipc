#include "TIPtreeSimpleVisitor.h"
#include <iostream>

void TIPtreeSimpleVisitor::visit_program(TIPtree::Program  *element) {
    std::cout << "visit_program" << std::endl;
    for (auto &fn : element->FUNCTIONS) {
        fn->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_function(TIPtree::Function  * element) {
    std::cout << "visit_function" << std::endl;
    for (auto  &decl : element->DECLS) {
        decl->accept(this);
    }

    for (auto  &stmt : element->BODY) {
        stmt->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_numberExpr(TIPtree::NumberExpr  * element) {
    std::cout << "visit_numberExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_variableExpr (TIPtree::VariableExpr  * element) {
    std::cout << "visit_variableExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_binaryExpr(TIPtree::BinaryExpr  * element) {
    std::cout << "visit_binaryExpr" << std::endl;
    element->LHS->accept(this);
    element->RHS->accept(this);
}

void TIPtreeSimpleVisitor::visit_inputExpr(TIPtree::InputExpr  * element) {
    std::cout << "visit_inputExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_funAppExpr (TIPtree::FunAppExpr  * element) {
    std::cout << "visit_funAppExpr" << std::endl;
    element->FUN->accept(this);
    for (auto  &arg : element->ACTUALS) {
        arg->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_allocExpr(TIPtree::AllocExpr  * element) {
    std::cout << "visit_allocExpr" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_refExpr (TIPtree::RefExpr  * element) {
    std::cout << "visit_refExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_deRefExpr (TIPtree::DeRefExpr  * element) {
    std::cout << "visit_deRefExpr" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_nullExpr(TIPtree::NullExpr  * element) {
    std::cout << "visit_nullExpr" << std::endl;
}

void TIPtreeSimpleVisitor::visit_declStmt(TIPtree::DeclStmt  * element) {
    std::cout << "visit_declStmt" << std::endl;
}

void TIPtreeSimpleVisitor::visit_assignStmt (TIPtree::AssignStmt  * element) {
    std::cout << "visit_assignStmt" << std::endl;
    element->LHS->print();
    element->RHS->print();
}

void TIPtreeSimpleVisitor::visit_whileStmt(TIPtree::WhileStmt  * element) {
    std::cout << "visit_whileStmt" << std::endl;
    element->COND->accept(this);
    element->BODY->print();
}

void TIPtreeSimpleVisitor::visit_ifStmt(TIPtree::IfStmt  * element) {
    std::cout << "visit_ifStmt" << std::endl;
    element->COND->print();
    element->THEN->print();

    if (element->ELSE != nullptr) {
        element->ELSE->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_outputStmt(TIPtree::OutputStmt  * element) {
    std::cout << "visit_outputStmt" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_returnStmt(TIPtree::ReturnStmt  * element) {
    std::cout << "visit_returnStmt" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_fieldExpr(TIPtree::FieldExpr  * element) {
    std::cout << "visit_fieldExp" << std::endl;
    element->INIT->accept(this);
}

void TIPtreeSimpleVisitor::visit_recordExpr(TIPtree::RecordExpr  * element) {
    std::cout << "visit_recordEpr" << std::endl;
    for (auto  &field : element->FIELDS) {
        field->accept(this);
    }
}

void TIPtreeSimpleVisitor::visit_accessExpr(TIPtree::AccessExpr  * element) {
    std::cout << "visit_accessExp" << std::endl;
    element->RECORD->accept(this);
}

void TIPtreeSimpleVisitor::visit_errorStmt(TIPtree::ErrorStmt  * element) {
    std::cout << "visit_errorStmt" << std::endl;
    element->ARG->accept(this);
}

void TIPtreeSimpleVisitor::visit_blockStmt(TIPtree::BlockStmt  * element) {
    std::cout << "visit_blockStm" << std::endl;
    for (auto  &s : element->STMTS) {
        s->accept(this);
    }
}
