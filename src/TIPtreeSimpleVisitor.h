#ifndef TIPC_TIPTREESIMPLEVISITOR_H
#define TIPC_TIPTREESIMPLEVISITOR_H

#include "TIPtreeVisitor.h"
#include <string>

class TIPtreeSimpleVisitor: public TIPtreeVisitor {
public:
    void visit_program(TIPtree::Program const * element) const override;
    void visit_function(TIPtree::Function const * element) const override;
    void visit_numberExpr(TIPtree::NumberExpr const * element) const override;
    void visit_variableExpr (TIPtree::VariableExpr const * element) const override;
    void visit_binaryExpr(TIPtree::BinaryExpr const * element) const override;
    void visit_inputExpr(TIPtree::InputExpr const * element) const override;
    void visit_funAppExpr (TIPtree::FunAppExpr const * element) const override;
    void visit_allocExpr(TIPtree::AllocExpr const * element) const override;
    void visit_refExpr (TIPtree::RefExpr const * element) const override;
    void visit_deRefExpr (TIPtree::DeRefExpr const * element) const override;
    void visit_nullExpr(TIPtree::NullExpr const * element) const override;
    void visit_declStmt(TIPtree::DeclStmt const * element) const override;
    void visit_assignStmt (TIPtree::AssignStmt const * element) const override;
    void visit_whileStmt(TIPtree::WhileStmt const * element) const override;
    void visit_ifStmt(TIPtree::IfStmt const * element) const override;
    void visit_outputStmt(TIPtree::OutputStmt const * element) const override;
    void visit_returnStmt(TIPtree::ReturnStmt const * element) const override;
    void visit_fieldExpr(TIPtree::FieldExpr const * element) const override;
    void visit_recordExpr(TIPtree::RecordExpr const * element) const override;
    void visit_accessExpr(TIPtree::AccessExpr const * element) const override;
    void visit_errorStmt(TIPtree::ErrorStmt const * element) const override;
    void visit_blockStmt(TIPtree::BlockStmt const * element) const override;
};

#endif //TIPC_TIPTREESIMPLEVISITOR_H
