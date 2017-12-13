
// Generated from Grammar.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "GrammarVisitor.h"


/**
 * This class provides an empty implementation of GrammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  GrammarBaseVisitor : public GrammarVisitor {
public:

  virtual antlrcpp::Any visitProgram(GrammarParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatements(GrammarParser::StatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitListStatement(GrammarParser::ListStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(GrammarParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignment(GrammarParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStatement(GrammarParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfChainStatement(GrammarParser::IfChainStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElseStatements(GrammarParser::ElseStatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileStatement(GrammarParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDoWhileStatement(GrammarParser::DoWhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr(GrammarParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprLogical(GrammarParser::ExprLogicalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprCompare(GrammarParser::ExprCompareContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprAddSub(GrammarParser::ExprAddSubContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprMulDivModEtc(GrammarParser::ExprMulDivModEtcContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentExpr(GrammarParser::IdentExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

