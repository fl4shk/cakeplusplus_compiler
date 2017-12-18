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

	std::stack<s64> __num_stack;
	std::stack<std::string*> __str_stack;

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
	antlrcpp::Any visitFuncArgExpr
		(GrammarParser::FuncArgExprContext *ctx);

	antlrcpp::Any visitStatements
		(GrammarParser::StatementsContext *ctx);
	antlrcpp::Any visitStatement
		(GrammarParser::StatementContext *ctx);

	antlrcpp::Any visitVarDecl
		(GrammarParser::VarDeclContext *ctx);
	antlrcpp::Any visitFuncArgDecl
		(GrammarParser::FuncArgDeclContext *ctx);

	antlrcpp::Any visitBuiltinTypename
		(GrammarParser::BuiltinTypenameContext *ctx);


	antlrcpp::Any visitNonSizedArrayIdentName
		(GrammarParser::NonSizedArrayIdentNameContext *ctx);
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

	antlrcpp::Any visitExprUnary
		(GrammarParser::ExprUnaryContext *ctx);
	antlrcpp::Any visitExprBitInvert
		(GrammarParser::ExprBitInvertContext *ctx);
	antlrcpp::Any visitExprNegate
		(GrammarParser::ExprNegateContext *ctx);
	antlrcpp::Any visitExprLogNot
		(GrammarParser::ExprLogNotContext *ctx);


	antlrcpp::Any visitIdentExpr
		(GrammarParser::IdentExprContext *ctx);
	antlrcpp::Any visitIdentDecl
		(GrammarParser::IdentDeclContext *ctx);
	antlrcpp::Any visitIdentName
		(GrammarParser::IdentNameContext *ctx);

	antlrcpp::Any visitNumExpr
		(GrammarParser::NumExprContext *ctx);

	antlrcpp::Any visitLenExpr
		(GrammarParser::LenExprContext *ctx);
	antlrcpp::Any visitSizeofExpr
		(GrammarParser::SizeofExprContext *ctx);

	antlrcpp::Any visitSubscriptExpr
		(GrammarParser::SubscriptExprContext *ctx);

	antlrcpp::Any visitSubscriptConst
		(GrammarParser::SubscriptConstContext *ctx);

protected:		// functions
	inline void push_num(s64 to_push)
	{
		__num_stack.push(to_push);
	}
	inline auto pop_num()
	{
		auto ret = __num_stack.top(); 
		__num_stack.pop();
		return ret;
	}
	inline auto get_top_num()
	{
		return __num_stack.top();
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
	inline auto get_top_str()
	{
		return __str_stack.top();
	}
	inline auto& curr_func()
	{
		return *__curr_func;
	}
	inline auto& sym_tbl()
	{
		return curr_func().sym_tbl();
	}
};

#endif		// compiler_class_hpp
