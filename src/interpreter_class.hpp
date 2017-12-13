#ifndef interpreter_class_hpp
#define interpreter_class_hpp

#include "misc_includes.hpp"
#include "gen_src/GrammarLexer.h"
#include "gen_src/GrammarParser.h"
#include "gen_src/GrammarVisitor.h"

#include "symbol_table_class.hpp"

#include <stack>


class Interpreter : public GrammarVisitor
{
protected:		// variables
	Json::Value __output_root;
	std::stack<int> __num_stack;
	std::stack<std::string*> __str_stack;
	SymbolTable __sym_tbl;

public:		// functions
	virtual ~Interpreter();
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

    antlrcpp::Any visitVarDecl
    	(GrammarParser::VarDeclContext *ctx);
    antlrcpp::Any visitPutNStatement
    	(GrammarParser::PutNStatementContext *ctx);
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

protected:		// functions
	inline void push_num(int to_push)
	{
		__num_stack.push(to_push);
	}
	inline auto pop_num()
	{
		auto ret = __num_stack.top(); 
		__num_stack.pop();
		return ret;
	}

	inline void push_str(std::string* to_push)
	{
		__str_stack.push(to_push);
	}
	inline auto pop_str()
	{
		auto ret = __str_stack.top(); 
		__str_stack.pop();
		return ret;
	}

	//void get_subscript(std::vector<int>& ret);

};


#endif		// interpreter_class_hpp
