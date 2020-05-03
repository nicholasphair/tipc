#include "TIPtreeTypeConstraintVisitor.h"
#include <iostream>
#include <TipVar.hpp>
#include <TipFunction.hpp>
#include <TipAlpha.hpp>
#include "TipRef.hpp"
#include "TipInt.hpp"

std::vector<TypeConstraint> TIPtreeTypeConstraintVisitor::get_constraints() {
    return constraints;
}

void TIPtreeTypeConstraintVisitor::visit_program(TIPtree::Program  *element) {
    for (auto &fn : element->FUNCTIONS) {
        fn->accept(this);

        if(fn->NAME == "main") {
            for(auto &formal : fn->FORMALS) {
                TipVar * var = safeTipVarGenerate(formal);
                TipInt * tipInt = new TipInt();
                TypeConstraint constraint(var, tipInt);
                constraints.push_back(constraint);
            }
            auto ret = safeTipVarGenerate(fn->BODY.back().get());
            TipInt * tipInt = new TipInt();
            TypeConstraint constraint(ret, tipInt);
            constraints.push_back(constraint);
        }

    }
}

// Function declaration
void TIPtreeTypeConstraintVisitor::visit_function(TIPtree::Function  * element) {
    std::vector<Term *> args;
    for(auto &formal : element->FORMALS) {
        TipVar * var = safeTipVarGenerate(formal);
        args.push_back(var);
    }

    for (auto  &decl : element->DECLS) {
        decl->accept(this);
    }

    for (auto  &stmt : element->BODY) {
        stmt->accept(this);
    }

    auto n = element->getName();
    TipVar * tipVar = safeTipVarGenerate(n);
    auto ret = safeTipVarGenerate(element->BODY.back().get());
    TipFunction * tipFunction = new TipFunction(args, ret);
    TypeConstraint constraint(tipVar, tipFunction);
    constraints.push_back(constraint);
}

void TIPtreeTypeConstraintVisitor::visit_numberExpr(TIPtree::NumberExpr * element) {
    TipVar * tipVar = safeTipVarGenerate(element);
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);
}

void TIPtreeTypeConstraintVisitor::visit_variableExpr(TIPtree::VariableExpr * element) {
    //  Leaf node that is a variable. We cannot make any claim about the type of this expression.
}

void TIPtreeTypeConstraintVisitor::visit_binaryExpr(TIPtree::BinaryExpr  * element) {
    TipVar * e1 = safeTipVarGenerate(element->LHS.get());
    TipVar * e2 = safeTipVarGenerate(element->RHS.get());
    TipVar * e1_eq_e2 = safeTipVarGenerate(element);
    TipInt * tipInt = new TipInt();

    TypeConstraint constraint1(e1, e2);
    TypeConstraint constraint2(e1, e1_eq_e2);
    TypeConstraint constraint3(e1, tipInt);
    TypeConstraint constraint4(e2, e1_eq_e2);
    TypeConstraint constraint5(e2, tipInt);
    TypeConstraint constraint6(e1_eq_e2, tipInt);

    if(element->OP == "==") {
        constraints.push_back(constraint1);
        constraints.push_back(constraint6);
    } else {
        constraints.push_back(constraint1);
        constraints.push_back(constraint2);
        constraints.push_back(constraint3);
        constraints.push_back(constraint4);
        constraints.push_back(constraint5);
        constraints.push_back(constraint6);
    }

    element->LHS->accept(this);
    element->RHS->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_inputExpr(TIPtree::InputExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);
}

void TIPtreeTypeConstraintVisitor::visit_funAppExpr (TIPtree::FunAppExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);

    element->FUN->accept(this);
    std::vector<Term *> actuals;
    for (auto  &arg : element->ACTUALS) {
        arg->accept(this);
        actuals.push_back(safeTipVarGenerate(arg.get()));
    }

    TipVar * application = safeTipVarGenerate(element->FUN.get());
    TipFunction * f = new TipFunction(actuals, application);
    TypeConstraint constraint(tipVar, f);
    constraints.push_back(constraint);
}

void TIPtreeTypeConstraintVisitor::visit_allocExpr(TIPtree::AllocExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);
    TipVar * tipVar2 = safeTipVarGenerate(element->ARG.get());
    TipRef * tipRef = new TipRef(tipVar2);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);

    element->ARG->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_refExpr (TIPtree::RefExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);
    TipVar * tipVar2 = safeTipVarGenerate(&canonicals.at(element->NAME));
    TipRef * tipRef = new TipRef(tipVar2);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);
}

void TIPtreeTypeConstraintVisitor::visit_deRefExpr (TIPtree::DeRefExpr * element) {
    TipVar * tipVar = safeTipVarGenerate(element->ARG.get());
    TipVar * tipVar2 = safeTipVarGenerate(element);
    TipRef * tipRef = new TipRef(tipVar2);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);

    element->ARG->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_nullExpr(TIPtree::NullExpr  * element) {
    TipVar * tipVar = safeTipVarGenerate(element);
    TipAlpha * tipAlpha = new TipAlpha("");
    TipRef * tipRef = new TipRef(tipAlpha);
    TypeConstraint constraint(tipVar, tipRef);
    constraints.push_back(constraint);
}

void TIPtreeTypeConstraintVisitor::visit_declStmt(TIPtree::DeclStmt  * element) {
    // Variable Declarations make no constraints.
}

void TIPtreeTypeConstraintVisitor::visit_assignStmt (TIPtree::AssignStmt  * element) {
    auto lhs = element->LHS.get();
    auto rhs = element->RHS.get();

    if(auto l = dynamic_cast<TIPtree::DeRefExpr *>(lhs)) {
        TipVar * lvar = safeTipVarGenerate(l->ARG.get());
        TipVar * rvar = safeTipVarGenerate(element->RHS.get());
        TipRef * rref = new TipRef(rvar);
        TypeConstraint constraint(lvar, rref);
        constraints.push_back(constraint);
    } else {
        TipVar * lvar = safeTipVarGenerate(element->LHS.get());
        TipVar * rvar = safeTipVarGenerate(element->RHS.get());
        TypeConstraint constraint(lvar, rvar);
        constraints.push_back(constraint);

        //element->LHS->accept(this);
    }
    element->RHS->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_whileStmt(TIPtree::WhileStmt  * element) {
    TipVar * tipVar = safeTipVarGenerate(element->COND.get());
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    element->COND->accept(this);
    element->BODY->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_ifStmt(TIPtree::IfStmt  * element) {
    TipVar * tipVar = safeTipVarGenerate(element->COND.get());
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    element->COND->accept(this);
    element->THEN->accept(this);

    if (element->ELSE != nullptr) {
        element->ELSE->accept(this);
    }
}

void TIPtreeTypeConstraintVisitor::visit_outputStmt(TIPtree::OutputStmt  * element) {
    TipVar * tipVar = safeTipVarGenerate(element->ARG.get());
    TipInt * tipInt = new TipInt();
    TypeConstraint constraint(tipVar, tipInt);
    constraints.push_back(constraint);

    element->ARG->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_returnStmt(TIPtree::ReturnStmt  * element) {
    // We cannot say anything about a return stmt.
    element->ARG->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_fieldExpr(TIPtree::FieldExpr  * element) {
    element->INIT->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_recordExpr(TIPtree::RecordExpr  * element) {
    for (auto  &field : element->FIELDS) {
        field->accept(this);
    }
}

void TIPtreeTypeConstraintVisitor::visit_accessExpr(TIPtree::AccessExpr  * element) {
    element->RECORD->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_errorStmt(TIPtree::ErrorStmt  * element) {
    element->ARG->accept(this);
}

void TIPtreeTypeConstraintVisitor::visit_blockStmt(TIPtree::BlockStmt  * element) {
    for (auto  &s : element->STMTS) {
        s->accept(this);
    }
}

TipVar * TIPtreeTypeConstraintVisitor::safeTipVarGenerate(std::string name) {
    return new TipVar(&canonicals.at(name));
}

TipVar * TIPtreeTypeConstraintVisitor::safeTipVarGenerate(TIPtree::Node * node) {
    if(canonicals.count(node->print()) != 0) {
        return new TipVar(&canonicals.at(node->print()));
    }
    return new TipVar(node);
}