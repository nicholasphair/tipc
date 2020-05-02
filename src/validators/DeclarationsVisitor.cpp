#include "DeclarationsVisitor.hpp"

#include <iostream>
/* this is a hack because there are no nodes for identifiers. For each usage of an identifier we cant
 * a consistent canonical representation of it. The tip impl maps each identifier to its declaration. They
 * can do that because, vars, program decls, and program args all fall under that umbrella. We don't have that
 * luxury. Vars are declar but function names and params are just strings.
 *
 * What we need is an umbrella ~type~ for all of these and always use that..
 */

std::map<std::string, TIPtree::Identifier> DeclarationsVisitor::get_canonicals() {
    return canonicals;
}

void DeclarationsVisitor::visit_program(TIPtree::Program * element) {
    for (auto &fn : element->FUNCTIONS) {
        fn->accept(this);
    }
}

void DeclarationsVisitor::visit_function(TIPtree::Function * element) {
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
}


void DeclarationsVisitor::visit_declStmt(TIPtree::DeclStmt  * element) {
    for(auto name : element->VARS) {
        TIPtree::Identifier identifier(name);
        canonicals.emplace(name, identifier);
    }
}

void DeclarationsVisitor::visit_funAppExpr (TIPtree::FunAppExpr * element) {}
void DeclarationsVisitor::visit_numberExpr(TIPtree::NumberExpr * element) {}
void DeclarationsVisitor::visit_variableExpr (TIPtree::VariableExpr * element) {}
void DeclarationsVisitor::visit_binaryExpr(TIPtree::BinaryExpr * element) {}
void DeclarationsVisitor::visit_inputExpr(TIPtree::InputExpr * element) {}
void DeclarationsVisitor::visit_allocExpr(TIPtree::AllocExpr * element) {}
void DeclarationsVisitor::visit_refExpr (TIPtree::RefExpr * element) {}
void DeclarationsVisitor::visit_deRefExpr (TIPtree::DeRefExpr * element) {}
void DeclarationsVisitor::visit_nullExpr(TIPtree::NullExpr * element) {}
void DeclarationsVisitor::visit_assignStmt (TIPtree::AssignStmt * element) {}
void DeclarationsVisitor::visit_whileStmt(TIPtree::WhileStmt * element) {}
void DeclarationsVisitor::visit_ifStmt(TIPtree::IfStmt * element) {}
void DeclarationsVisitor::visit_outputStmt(TIPtree::OutputStmt * element) {}
void DeclarationsVisitor::visit_returnStmt(TIPtree::ReturnStmt * element) {}
void DeclarationsVisitor::visit_fieldExpr(TIPtree::FieldExpr * element) {}
void DeclarationsVisitor::visit_recordExpr(TIPtree::RecordExpr * element) {}
void DeclarationsVisitor::visit_accessExpr(TIPtree::AccessExpr * element) {}
void DeclarationsVisitor::visit_errorStmt(TIPtree::ErrorStmt * element) {}
void DeclarationsVisitor::visit_blockStmt(TIPtree::BlockStmt * element) {}
