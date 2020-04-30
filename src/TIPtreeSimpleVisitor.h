#ifndef TIPC_TIPTREESIMPLEVISITOR_H
#define TIPC_TIPTREESIMPLEVISITOR_H

#include "TIPtreeVisitor.h"
#include <string>

class TIPtreeSimpleVisitor: public TIPtreeVisitor {
public:
    void visit_program(TIPtree::Program  * element) override;
    void visit_function(TIPtree::Function  * element) override;
    void visit_numberExpr(TIPtree::NumberExpr  * element) override;
    void visit_variableExpr (TIPtree::VariableExpr  * element) override;
    void visit_binaryExpr(TIPtree::BinaryExpr  * element) override;
    void visit_inputExpr(TIPtree::InputExpr  * element) override;
    void visit_funAppExpr (TIPtree::FunAppExpr  * element) override;
    void visit_allocExpr(TIPtree::AllocExpr  * element) override;
    void visit_refExpr (TIPtree::RefExpr  * element) override;
    void visit_deRefExpr (TIPtree::DeRefExpr  * element) override;
    void visit_nullExpr(TIPtree::NullExpr  * element) override;
    void visit_declStmt(TIPtree::DeclStmt  * element) override;
    void visit_assignStmt (TIPtree::AssignStmt  * element) override;
    void visit_whileStmt(TIPtree::WhileStmt  * element) override;
    void visit_ifStmt(TIPtree::IfStmt  * element) override;
    void visit_outputStmt(TIPtree::OutputStmt  * element) override;
    void visit_returnStmt(TIPtree::ReturnStmt  * element) override;
    void visit_fieldExpr(TIPtree::FieldExpr  * element) override;
    void visit_recordExpr(TIPtree::RecordExpr  * element) override;
    void visit_accessExpr(TIPtree::AccessExpr  * element) override;
    void visit_errorStmt(TIPtree::ErrorStmt  * element) override;
    void visit_blockStmt(TIPtree::BlockStmt  * element) override;
};

#endif //TIPC_TIPTREESIMPLEVISITOR_H
