
// Generated from Grammar.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "GrammarParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by GrammarParser.
 */
class  GrammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by GrammarParser.
   */
    virtual antlrcpp::Any visitProgram(GrammarParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitStatements(GrammarParser::StatementsContext *context) = 0;

    virtual antlrcpp::Any visitListStatement(GrammarParser::ListStatementContext *context) = 0;

    virtual antlrcpp::Any visitStatement(GrammarParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitAssignment(GrammarParser::AssignmentContext *context) = 0;

    virtual antlrcpp::Any visitIfStatement(GrammarParser::IfStatementContext *context) = 0;

    virtual antlrcpp::Any visitIfChainStatement(GrammarParser::IfChainStatementContext *context) = 0;

    virtual antlrcpp::Any visitElseStatements(GrammarParser::ElseStatementsContext *context) = 0;

    virtual antlrcpp::Any visitWhileStatement(GrammarParser::WhileStatementContext *context) = 0;

    virtual antlrcpp::Any visitDoWhileStatement(GrammarParser::DoWhileStatementContext *context) = 0;

    virtual antlrcpp::Any visitExpr(GrammarParser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitExprLogical(GrammarParser::ExprLogicalContext *context) = 0;

    virtual antlrcpp::Any visitExprCompare(GrammarParser::ExprCompareContext *context) = 0;

    virtual antlrcpp::Any visitExprAddSub(GrammarParser::ExprAddSubContext *context) = 0;

    virtual antlrcpp::Any visitExprMulDivModEtc(GrammarParser::ExprMulDivModEtcContext *context) = 0;

    virtual antlrcpp::Any visitIdentExpr(GrammarParser::IdentExprContext *context) = 0;


};

