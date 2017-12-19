#ifndef frontend_class_hpp
#define frontend_class_hpp

#include "misc_includes.hpp"
#include "gen_src/GrammarLexer.h"
#include "gen_src/GrammarParser.h"
#include "gen_src/GrammarVisitor.h"

#include "symbol_table_classes.hpp"
//#include "abstract_syntax_tree_classes.hpp"
//#include "code_generator_class.hpp"
#include "vm_code_class.hpp"


class FrntErrorListener : public antlr4::ANTLRErrorListener
{
public:		// functions
	virtual ~FrntErrorListener();

	void syntaxError(antlr4::Recognizer *recognizer, 
		antlr4::Token *offendingSymbol, size_t line, 
		size_t charPositionInLine, const std::string &msg, 
		std::exception_ptr e);
	void reportAmbiguity(antlr4::Parser *recognizer, 
		const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, 
		bool exact, const antlrcpp::BitSet &ambigAlts, 
		antlr4::atn::ATNConfigSet *configs);
	
	void reportAttemptingFullContext(antlr4::Parser *recognizer, 
		const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
		const antlrcpp::BitSet &conflictingAlts, 
		antlr4::atn::ATNConfigSet *configs);

	void reportContextSensitivity(antlr4::Parser *recognizer, 
		const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
		size_t prediction, antlr4::atn::ATNConfigSet *configs);
};

class Frontend : public GrammarVisitor
{
public:		// typedefs
	//typedef std::vector<AstNode*> AstVec;

protected:		// variables

	// Table of functions
	FunctionTable __func_tbl;

	// Current function
	Function* __curr_func;


	//std::stack<AstNode*> __ast_node_stack;


	std::stack<s64> __num_stack;
	std::stack<std::string*> __str_stack;
	std::stack<BuiltinTypename> __builtin_typename_stack;
	std::stack<VmCode*> __code_stack;

	//AstNode* __program_node;

	//CodeGenerator __codegen;

public:		// functions
	virtual ~Frontend();

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
	antlrcpp::Any visitStmt
		(GrammarParser::StmtContext *ctx);

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
	antlrcpp::Any visitReturnExprStatement
		(GrammarParser::ReturnExprStatementContext *ctx);
	antlrcpp::Any visitReturnNothingStatement
		(GrammarParser::ReturnNothingStatementContext *ctx);

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
	inline void err(const std::string& msg)
	{
		printerr(msg);
		exit(1);
	}

	inline auto& curr_func()
	{
		return *__curr_func;
	}
	inline auto& sym_tbl()
	{
		return curr_func().sym_tbl();
	}

	inline void push_code(VmCode* to_push)
	{
		__code_stack.push(to_push);
	}
	inline auto pop_code()
	{
		auto ret = __code_stack.top();
		__code_stack.pop();
		return ret;
	}
	inline auto get_top_code()
	{
		return __code_stack.top();
	}

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

	inline void push_builtin_typename(BuiltinTypename to_push)
	{
		__builtin_typename_stack.push(to_push);
	}
	inline auto pop_builtin_typename()
	{
		auto ret = __builtin_typename_stack.top(); 
		__builtin_typename_stack.pop();
		return ret;
	}
	inline auto get_top_builtin_typename()
	{
		return __builtin_typename_stack.top();
	}


};

#endif		// frontend_class_hpp