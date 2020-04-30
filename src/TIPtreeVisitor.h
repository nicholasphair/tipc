#ifndef TIPC_TIPTREEVISITOR_H
#define TIPC_TIPTREEVISITOR_H
#include "TIPtree.h"


//namespace TIPtree {
//    class Program;
//    class Program;
//    class Function;
//    class NumberExpr;
//    class VariableExpr;
//    class BinaryExpr;
//    class InputExpr;
//    class FunAppExpr;
//    class AllocExpr;
//    class RefExpr;
//    class DeRefExpr;
//    class NullExpr;
//    class DeclStmt;
//    class AssignStmt;
//    class WhileStmt;
//    class IfStmt;
//    class OutputStmt;
//    class ReturnStmt;
//    class FieldExpr;
//    class RecordExpr;
//    class AccessExpr;
//    class ErrorStmt;
//    class BlockStmt;
//}

class TIPtreeVisitor {
public:
    virtual void visit_program(TIPtree::Program const * element) const = 0;
    virtual void visit_function(TIPtree::Function const * element) const = 0;
    virtual void visit_numberExpr(TIPtree::NumberExpr const * element) const = 0;
    virtual void visit_variableExpr (TIPtree::VariableExpr const * element) const = 0;
    virtual void visit_binaryExpr(TIPtree::BinaryExpr const * element) const = 0;
    virtual void visit_inputExpr(TIPtree::InputExpr const * element) const = 0;
    virtual void visit_funAppExpr (TIPtree::FunAppExpr const * element) const = 0;
    virtual void visit_allocExpr(TIPtree::AllocExpr const * element) const = 0;
    virtual void visit_refExpr (TIPtree::RefExpr const * element) const = 0;
    virtual void visit_deRefExpr (TIPtree::DeRefExpr const * element) const = 0;
    virtual void visit_nullExpr(TIPtree::NullExpr const * element) const = 0;
    virtual void visit_declStmt(TIPtree::DeclStmt const * element) const = 0;
    virtual void visit_assignStmt (TIPtree::AssignStmt const * element) const = 0;
    virtual void visit_whileStmt(TIPtree::WhileStmt const * element) const = 0;
    virtual void visit_ifStmt(TIPtree::IfStmt const * element) const = 0;
    virtual void visit_outputStmt(TIPtree::OutputStmt const * element) const = 0;
    virtual void visit_returnStmt(TIPtree::ReturnStmt const * element) const = 0;
    virtual void visit_fieldExpr(TIPtree::FieldExpr const * element) const = 0;
    virtual void visit_recordExpr(TIPtree::RecordExpr const * element) const = 0;
    virtual void visit_accessExpr(TIPtree::AccessExpr const * element) const = 0;
    virtual void visit_errorStmt(TIPtree::ErrorStmt const * element) const = 0;
    virtual void visit_blockStmt(TIPtree::BlockStmt const * element) const = 0;
};


#endif //TIPC_TIPTREEVISITOR_H
