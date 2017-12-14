#ifndef compiler_class_hpp
#define compiler_class_hpp

#include "misc_includes.hpp"
#include "gen_src/GrammarLexer.h"
#include "gen_src/GrammarParser.h"
#include "gen_src/GrammarVisitor.h"

#include "symbol_table_classes.hpp"

class Compiler : public GrammarVisitor
{
protected:		// variables
	// Table of functions
	FunctionTable __func_tbl;

	// Current function
	Function* __curr_func;
	//std::stack<VmCode*> __code_stack;

public:		// functions
	virtual ~Compiler();
	/**
	* Visit parse trees produced by GrammarParser.
	*/
	antlrcpp::Any visitProgram
		(GrammarParser::ProgramContext *ctx);

	antlrcpp::Any visitFuncDecl
		(GrammarParser::FuncDeclContext *ctx);

	antlrcpp::Any visitFuncCall
		(GrammarParser::FuncCallContext *ctx);


	antlrcpp::Any visitStatements
		(GrammarParser::StatementsContext *ctx);

	antlrcpp::Any visitStatement
		(GrammarParser::StatementContext *ctx);

    antlrcpp::Any visitVarDecl
    	(GrammarParser::VarDeclContext *ctx);
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
	antlrcpp::Any visitIdentDecl
		(GrammarParser::IdentDeclContext *ctx);
	antlrcpp::Any visitIdentName
		(GrammarParser::IdentNameContext *ctx);

	antlrcpp::Any visitNumExpr
		(GrammarParser::NumExprContext *ctx);

	antlrcpp::Any visitSubscriptExpr
		(GrammarParser::SubscriptExprContext *ctx);

	antlrcpp::Any visitSubscriptConst
		(GrammarParser::SubscriptConstContext *ctx);
};

#endif		// compiler_class_hpp
