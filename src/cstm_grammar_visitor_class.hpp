#ifndef cstm_grammar_visitor_class_hpp
#define cstm_grammar_visitor_class_hpp

#include "misc_includes.hpp"
#include "gen_src/GrammarLexer.h"
#include "gen_src/GrammarParser.h"
#include "gen_src/GrammarVisitor.h"


class CstmGrammarVisitor : public GrammarVisitor
{
protected:		// variables
	Json::Value __output_root;

public:		// functions
	virtual ~CstmGrammarVisitor();
	/**
	* Visit parse trees produced by GrammarParser.
	*/
	antlrcpp::Any visitProgram
		(GrammarParser::ProgramContext *ctx);

	antlrcpp::Any visitStatements
		(GrammarParser::StatementsContext *ctx);

	antlrcpp::Any visitListStatement
		(GrammarParser::ListStatementContext *ctx);

	antlrcpp::Any visitStatement
		(GrammarParser::StatementContext *ctx);

	antlrcpp::Any visitAssignment
		(GrammarParser::AssignmentContext *ctx);
	antlrcpp::Any visitIfStatement
		(GrammarParser::IfStatementContext *ctx);
	antlrcpp::Any visitIfChainStatement
		(GrammarParser::IfChainStatementContext *ctx);
	antlrcpp::Any visitElseStatements
		(GrammarParser::ElseStatementsContext *ctx);
	antlrcpp::Any visitWhileStatement
		(GrammarParser::WhileStatementContext *ctx);
	antlrcpp::Any visitDoWhileStatement
		(GrammarParser::DoWhileStatementContext *ctx);

	antlrcpp::Any visitExpr
		(GrammarParser::ExprContext *ctx);
	antlrcpp::Any visitExprLogical
		(GrammarParser::ExprLogicalContext *ctx);
	antlrcpp::Any visitExprCompare
		(GrammarParser::ExprCompareContext *ctx);
	antlrcpp::Any visitExprAddSub
		(GrammarParser::ExprAddSubContext *ctx);
	antlrcpp::Any visitExprMulDivModEtc
		(GrammarParser::ExprMulDivModEtcContext *ctx);
	antlrcpp::Any visitIdentExpr
		(GrammarParser::IdentExprContext *ctx);


};


#endif		// cstm_grammar_visitor_class_hpp
