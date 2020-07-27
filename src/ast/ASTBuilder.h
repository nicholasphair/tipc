#pragma once

#include <string>
#include <optional>

#include "antlr4-runtime.h"
#include "TIPParser.h"
#include "TIPBaseVisitor.h"

#include "AST.h"

using namespace antlrcpp;

class ASTBuilder : public TIPBaseVisitor {
private:
  TIPParser *parser;
  std::string opString(int op);

public:
  ASTBuilder(TIPParser *parser);

  /*
   * If AST is built without error then a unique pointer to it is 
   * found in the value() of the returned result, oherwise 
   * std::nullopt is returned.
   */
  std::optional<std::unique_ptr<ASTProgram>> build(TIPParser::ProgramContext *ctx);

  Any visitFunction(TIPParser::FunctionContext *ctx) override;
  Any visitNegNumber(TIPParser::NegNumberContext *ctx) override;
  Any visitAdditiveExpr(TIPParser::AdditiveExprContext *ctx) override;
  Any visitRelationalExpr(TIPParser::RelationalExprContext *ctx) override;
  Any visitMultiplicativeExpr(
      TIPParser::MultiplicativeExprContext *ctx) override;
  Any visitEqualityExpr(TIPParser::EqualityExprContext *ctx) override;
  Any visitParenExpr(TIPParser::ParenExprContext *ctx) override;
  Any visitNumExpr(TIPParser::NumExprContext *ctx) override;
  Any visitVarExpr(TIPParser::VarExprContext *ctx) override;
  Any visitInputExpr(TIPParser::InputExprContext *ctx) override;
  Any visitFunAppExpr(TIPParser::FunAppExprContext *ctx) override;
  Any visitAllocExpr(TIPParser::AllocExprContext *ctx) override;
  Any visitRefExpr(TIPParser::RefExprContext *ctx) override;
  Any visitDeRefExpr(TIPParser::DeRefExprContext *ctx) override;
  Any visitNullExpr(TIPParser::NullExprContext *ctx) override;
  Any visitRecordExpr(TIPParser::RecordExprContext *ctx) override;
  Any visitFieldExpr(TIPParser::FieldExprContext *ctx) override;
  Any visitAccessExpr(TIPParser::AccessExprContext *ctx) override;
  Any visitDeclaration(TIPParser::DeclarationContext *ctx) override;
  Any visitNameDeclaration(TIPParser::NameDeclarationContext *ctx) override;
  Any visitAssignmentStmt(TIPParser::AssignmentStmtContext *ctx) override;
  Any visitBlockStmt(TIPParser::BlockStmtContext *ctx) override;
  Any visitWhileStmt(TIPParser::WhileStmtContext *ctx) override;
  Any visitIfStmt(TIPParser::IfStmtContext *ctx) override;
  Any visitOutputStmt(TIPParser::OutputStmtContext *ctx) override;
  Any visitErrorStmt(TIPParser::ErrorStmtContext *ctx) override;
  Any visitReturnStmt(TIPParser::ReturnStmtContext *ctx) override;
};