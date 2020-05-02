#include "DeclarationsVisitor.hpp"
#include <iostream>

std::map<std::string, TIPtree::Identifier> DeclarationsVisitor::get_canonicals() {
    return canonicals;
}


void DeclarationsVisitor::visit_program(TIPtree::Program  *element) {
    for (auto &fn : element->FUNCTIONS) {
        fn->accept(this);
    }
}

void DeclarationsVisitor::visit_function(TIPtree::Function  * element) {
    std::string name = element->NAME;
    TIPtree::Identifier identifier(name);
    canonicals.emplace(name, identifier);

    for(auto &formal : element->FORMALS) {
        TIPtree::Identifier identifier(formal);
        canonicals.emplace(formal, identifier);
    }

    for (auto  &decl : element->DECLS) {
        decl->accept(this);
    }

    for (auto  &stmt : element->BODY) {
        stmt->accept(this);
    }
}

void DeclarationsVisitor::visit_numberExpr(TIPtree::NumberExpr  * element) {
    auto name = element->print();
    TIPtree::Identifier identifier(name);
    canonicals.emplace(name, identifier);
    std::cout << "visit_numberExpr" << std::endl;
}

void DeclarationsVisitor::visit_variableExpr (TIPtree::VariableExpr  * element) {
    auto name = element->print();
    TIPtree::Identifier identifier(name);
    canonicals.emplace(name, identifier);
    std::cout << "visit_variableExpr" << std::endl;
}

void DeclarationsVisitor::visit_binaryExpr(TIPtree::BinaryExpr  * element) {
    std::cout << "visit_binaryExpr" << std::endl;
    element->LHS->accept(this);
    element->RHS->accept(this);
}

void DeclarationsVisitor::visit_inputExpr(TIPtree::InputExpr  * element) {
    auto name = element->print();
    TIPtree::Identifier identifier(name);
    canonicals.emplace(name, identifier);
    std::cout << "visit_inputExpr" << std::endl;
}

void DeclarationsVisitor::visit_funAppExpr (TIPtree::FunAppExpr  * element) {
    std::cout << "visit_funAppExpr" << std::endl;
    element->FUN->accept(this);
    for (auto  &arg : element->ACTUALS) {
        arg->accept(this);
    }
}

void DeclarationsVisitor::visit_allocExpr(TIPtree::AllocExpr  * element) {
    auto name = element->print();
    TIPtree::Identifier identifier(name);
    canonicals.emplace(name, identifier);

    std::cout << "visit_allocExpr" << std::endl;
    element->ARG->accept(this);
}

void DeclarationsVisitor::visit_refExpr (TIPtree::RefExpr  * element) {
    auto name = element->print();
    TIPtree::Identifier identifier(name);
    canonicals.emplace(name, identifier);

    auto name2 = element->NAME;
    TIPtree::Identifier identifier2(name2);
    canonicals.emplace(name2, identifier2);
    std::cout << "visit_refExpr" << std::endl;
}

void DeclarationsVisitor::visit_deRefExpr (TIPtree::DeRefExpr  * element) {
    std::cout << "visit_deRefExpr" << std::endl;
    element->ARG->accept(this);
}

void DeclarationsVisitor::visit_nullExpr(TIPtree::NullExpr  * element) {
    auto name = element->print();
    TIPtree::Identifier identifier(name);
    canonicals.emplace(name, identifier);
    std::cout << "visit_nullExpr" << std::endl;
}

void DeclarationsVisitor::visit_declStmt(TIPtree::DeclStmt  * element) {
    for(auto name : element->VARS) {
        TIPtree::Identifier identifier(name);
        canonicals.emplace(name, identifier);
    }
    std::cout << "visit_declStmt" << std::endl;
}

void DeclarationsVisitor::visit_assignStmt (TIPtree::AssignStmt  * element) {
    std::cout << "visit_assignStmt" << std::endl;
    element->LHS->accept(this);
    element->RHS->accept(this);
}

void DeclarationsVisitor::visit_whileStmt(TIPtree::WhileStmt  * element) {
    std::cout << "visit_whileStmt" << std::endl;
    element->COND->accept(this);
    element->BODY->accept(this);
}

void DeclarationsVisitor::visit_ifStmt(TIPtree::IfStmt  * element) {
    std::cout << "visit_ifStmt" << std::endl;
    element->COND->accept(this);
    element->THEN->accept(this);

    if (element->ELSE != nullptr) {
        element->ELSE->accept(this);
    }
}

void DeclarationsVisitor::visit_outputStmt(TIPtree::OutputStmt  * element) {
    std::cout << "visit_outputStmt" << std::endl;
    element->ARG->accept(this);
}

void DeclarationsVisitor::visit_returnStmt(TIPtree::ReturnStmt  * element) {
    std::cout << "visit_returnStmt" << std::endl;
    element->ARG->accept(this);
}

void DeclarationsVisitor::visit_fieldExpr(TIPtree::FieldExpr  * element) {
    std::cout << "visit_fieldExp" << std::endl;
    element->INIT->accept(this);
}

void DeclarationsVisitor::visit_recordExpr(TIPtree::RecordExpr  * element) {
    std::cout << "visit_recordEpr" << std::endl;
    for (auto  &field : element->FIELDS) {
        field->accept(this);
    }
}

void DeclarationsVisitor::visit_accessExpr(TIPtree::AccessExpr  * element) {
    std::cout << "visit_accessExp" << std::endl;
    element->RECORD->accept(this);
}

void DeclarationsVisitor::visit_errorStmt(TIPtree::ErrorStmt  * element) {
    std::cout << "visit_errorStmt" << std::endl;
    element->ARG->accept(this);
}

void DeclarationsVisitor::visit_blockStmt(TIPtree::BlockStmt  * element) {
    std::cout << "visit_blockStm" << std::endl;
    for (auto  &s : element->STMTS) {
        s->accept(this);
    }
}
