#ifndef TIPC_TIPTREEVISITOR_H
#define TIPC_TIPTREEVISITOR_H
#include "TIPtree.h"

class TIPtreeVisitor {
public:
    virtual void visit_program(TIPtree::Program  * element)  = 0;
    virtual void visit_function(TIPtree::Function  * element) = 0;
    virtual void visit_numberExpr(TIPtree::NumberExpr  * element) = 0;
    virtual void visit_variableExpr (TIPtree::VariableExpr  * element) = 0;
    virtual void visit_binaryExpr(TIPtree::BinaryExpr  * element) = 0;
    virtual void visit_inputExpr(TIPtree::InputExpr  * element) = 0;
    virtual void visit_funAppExpr (TIPtree::FunAppExpr  * element) = 0;
    virtual void visit_allocExpr(TIPtree::AllocExpr  * element) = 0;
    virtual void visit_refExpr (TIPtree::RefExpr  * element) = 0;
    virtual void visit_deRefExpr (TIPtree::DeRefExpr  * element) = 0;
    virtual void visit_nullExpr(TIPtree::NullExpr  * element) = 0;
    virtual void visit_declStmt(TIPtree::DeclStmt  * element) = 0;
    virtual void visit_assignStmt (TIPtree::AssignStmt  * element) = 0;
    virtual void visit_whileStmt(TIPtree::WhileStmt  * element) = 0;
    virtual void visit_ifStmt(TIPtree::IfStmt  * element) = 0;
    virtual void visit_outputStmt(TIPtree::OutputStmt  * element) = 0;
    virtual void visit_returnStmt(TIPtree::ReturnStmt  * element) = 0;
    virtual void visit_fieldExpr(TIPtree::FieldExpr  * element) = 0;
    virtual void visit_recordExpr(TIPtree::RecordExpr  * element) = 0;
    virtual void visit_accessExpr(TIPtree::AccessExpr  * element) = 0;
    virtual void visit_errorStmt(TIPtree::ErrorStmt  * element) = 0;
    virtual void visit_blockStmt(TIPtree::BlockStmt  * element) = 0;
};


#endif //TIPC_TIPTREEVISITOR_H
