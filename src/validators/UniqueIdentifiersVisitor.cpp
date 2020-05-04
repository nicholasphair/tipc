#include "UniqueIdentifiersVisitor.hpp"

#include <iostream>

void UniqueIdentifiersVisitor::visit_program(TIPtree::Program  *element) {
    for (auto &fn : element->FUNCTIONS) {
        fn->accept(this);
    }
}

void UniqueIdentifiersVisitor::visit_function(TIPtree::Function  * element) {
    std::string name = element->NAME;
    int line = element->LINE;

    if(function_has_been_seen(name)) {
        conflicts.emplace_back(std::make_pair(name, line));
    }
    seen.insert(name);

    for(auto &formal : element->FORMALS) {
        if(arg_has_been_seen(formal)) {
            conflicts.emplace_back(std::make_pair(formal, line));
        }
        seen.insert(formal);
    }

    for (auto  &decl : element->DECLS) {
        decl->accept(this);
    }

    for (auto  &stmt : element->BODY) {
        stmt->accept(this);
    }
}

void UniqueIdentifiersVisitor::visit_numberExpr(TIPtree::NumberExpr  * element) {
}

void UniqueIdentifiersVisitor::visit_variableExpr (TIPtree::VariableExpr  * element) {
}

void UniqueIdentifiersVisitor::visit_binaryExpr(TIPtree::BinaryExpr  * element) {
    element->LHS->accept(this);
    element->RHS->accept(this);
}

void UniqueIdentifiersVisitor::visit_inputExpr(TIPtree::InputExpr  * element) {
}

void UniqueIdentifiersVisitor::visit_funAppExpr (TIPtree::FunAppExpr  * element) {
    element->FUN->accept(this);
    for (auto  &arg : element->ACTUALS) {
        arg->accept(this);
    }
}

void UniqueIdentifiersVisitor::visit_allocExpr(TIPtree::AllocExpr  * element) {
    element->ARG->accept(this);
}

void UniqueIdentifiersVisitor::visit_refExpr (TIPtree::RefExpr  * element) {
}

void UniqueIdentifiersVisitor::visit_deRefExpr (TIPtree::DeRefExpr  * element) {
    element->ARG->accept(this);
}

void UniqueIdentifiersVisitor::visit_nullExpr(TIPtree::NullExpr  * element) {
}

void UniqueIdentifiersVisitor::visit_declStmt(TIPtree::DeclStmt  * element) {
    int line = element->LINE;
    for(auto name : element->VARS) {
        if(decl_has_been_seen(name)) {
            conflicts.emplace_back(std::make_pair(name, line));
        }
        seen.insert(name);
    }
}

void UniqueIdentifiersVisitor::visit_assignStmt (TIPtree::AssignStmt  * element) {
    element->LHS->print();
    element->RHS->print();
}

void UniqueIdentifiersVisitor::visit_whileStmt(TIPtree::WhileStmt  * element) {
    element->COND->accept(this);
    element->BODY->print();
}

void UniqueIdentifiersVisitor::visit_ifStmt(TIPtree::IfStmt  * element) {
    element->COND->print();
    element->THEN->print();

    if (element->ELSE != nullptr) {
        element->ELSE->accept(this);
    }
}

void UniqueIdentifiersVisitor::visit_outputStmt(TIPtree::OutputStmt  * element) {
    element->ARG->accept(this);
}

void UniqueIdentifiersVisitor::visit_returnStmt(TIPtree::ReturnStmt  * element) {
    element->ARG->accept(this);
}

void UniqueIdentifiersVisitor::visit_fieldExpr(TIPtree::FieldExpr  * element) {
    element->INIT->accept(this);
}

void UniqueIdentifiersVisitor::visit_recordExpr(TIPtree::RecordExpr  * element) {
    for (auto  &field : element->FIELDS) {
        field->accept(this);
    }
}

void UniqueIdentifiersVisitor::visit_accessExpr(TIPtree::AccessExpr  * element) {
    element->RECORD->accept(this);
}

void UniqueIdentifiersVisitor::visit_errorStmt(TIPtree::ErrorStmt  * element) {
    element->ARG->accept(this);
}

void UniqueIdentifiersVisitor::visit_blockStmt(TIPtree::BlockStmt  * element) {
    for (auto  &s : element->STMTS) {
        s->accept(this);
    }
}

bool UniqueIdentifiersVisitor::function_has_been_seen(std::string function_name) {
    return seen.count(function_name) != 0;
}

bool UniqueIdentifiersVisitor::decl_has_been_seen(std::string decl) {
    return seen.count(decl) != 0;
}

bool UniqueIdentifiersVisitor::arg_has_been_seen(std::string arg) {
    return seen.count(arg) != 0;
}

bool UniqueIdentifiersVisitor::all_identifiers_unique() {
    return conflicts.empty();
}

std::vector<std::pair<std::string, int>> UniqueIdentifiersVisitor::get_conflicting_identifiers() {
    return conflicts;
}
