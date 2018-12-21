#ifndef src_compiler_class_hpp
#define src_compiler_class_hpp

// src/compiler_class.hpp

#include "misc_includes.hpp"
#include "alloc_stuff.hpp"

#include "ANTLRErrorListener.h"
#include "gen_src/CompilerGrammarLexer.h"
#include "gen_src/CompilerGrammarParser.h"
#include "gen_src/CompilerGrammarVisitor.h"

namespace cake_plus_plus
{

class Compiler : public CompilerGrammarVisitor
{
public:		// enums
	enum class ParsePass : size_t
	{
		FindExternalSymbols,
		FindLocalSymbols,
		SemanticAnalysis,
		GenInitialIr,
		Lim,
	};


public:		// typedefs
	typedef antlr4::ParserRuleContext ParserRuleContext;

private:		// variables
	CompilerGrammarParser::ProgramContext* _program_ctx;

	std::stack<PtrConstStr> _str_stack;
	std::stack<s64> _num_stack;
	ParsePass _parse_pass;

private:		// stack functions
	inline void _push_str(PtrConstStr to_push)
	{
		_str_stack.push(to_push);
	}
	inline auto _get_top_str()
	{
		return _str_stack.top();
	}
	inline auto _pop_str()
	{
		auto ret = _str_stack.top();
		_str_stack.pop();
		return ret;
	}
	inline void _push_num(s64 to_push)
	{
		_num_stack.push(to_push);
	}
	inline auto _get_top_num()
	{
		return _num_stack.top();
	}
	inline auto _pop_num()
	{
		auto ret = _num_stack.top();
		_num_stack.pop();
		return ret;
	}


public:		// functions
	Compiler(CompilerGrammarParser& parser);

	int run();

private:		// error/warning functions
	inline void _err(ParserRuleContext* ctx, const std::string& msg)
	{
		if (ctx == nullptr)
		{
			printerr("Error:  ", msg, "\n");
		}
		else
		{
			auto tok = ctx->getStart();
			const size_t line = tok->getLine();
			const size_t pos_in_line = tok->getCharPositionInLine();
			//printerr("Error in file \"", *__file_name, "\", on line ",
			//	line, ", position ", pos_in_line, ":  ", msg, "\n");
			printerr("Error on line ", line, ", position ", pos_in_line, 
				":  ", msg, "\n");
		}
		exit(1);
	}
	inline void _err(const std::string& msg)
	{
		//printerr("Error in file \"", *__file_name, "\":  ", msg, "\n");
		printerr("Error:  ", msg, "\n");
		exit(1);
	}


	inline void _warn(ParserRuleContext* ctx, const std::string& msg)
	{
		if (ctx == nullptr)
		{
			printerr("Error:  ", msg, "\n");
		}
		else
		{
			auto tok = ctx->getStart();
			const size_t line = tok->getLine();
			const size_t pos_in_line = tok->getCharPositionInLine();
			//printerr("Error in file \"", *__file_name, "\", on line ",
			//	line, ", position ", pos_in_line, ":  ", msg, "\n");
			printerr("Warning on line ", line, ", position ", pos_in_line, 
				":  ", msg, "\n");
		}
	}
	inline void _warn(const std::string& msg)
	{
		printerr("Warning:  ", msg, "\n");
	}

private:		// visitor functions
	antlrcpp::Any visitProgram
		(CompilerGrammarParser::ProgramContext *ctx);
	antlrcpp::Any visitListFunctions
		(CompilerGrammarParser::ListFunctionsContext *ctx);
	antlrcpp::Any visitFunction
		(CompilerGrammarParser::FunctionContext *ctx);


	// Function args
	antlrcpp::Any visitListFunctionArgs
		(CompilerGrammarParser::ListFunctionArgsContext *ctx);
	antlrcpp::Any visitFunctionArg
		(CompilerGrammarParser::FunctionArgContext *ctx);

	// Statements
	antlrcpp::Any visitListStatements
		(CompilerGrammarParser::ListStatementsContext *ctx);
	antlrcpp::Any visitStatement
		(CompilerGrammarParser::StatementContext *ctx);
	antlrcpp::Any visitScopedStatements
		(CompilerGrammarParser::ScopedStatementsContext *ctx);
	antlrcpp::Any visitStmtDeclVars
		(CompilerGrammarParser::StmtDeclVarsContext *ctx);
	antlrcpp::Any visitStmtAssign
		(CompilerGrammarParser::StmtAssignContext *ctx);
	antlrcpp::Any visitStmtIf
		(CompilerGrammarParser::StmtIfContext *ctx);
	antlrcpp::Any visitStmtElse
		(CompilerGrammarParser::StmtElseContext *ctx);
	antlrcpp::Any visitStmtWhile
		(CompilerGrammarParser::StmtWhileContext *ctx);

	// Expressions
	antlrcpp::Any visitExpr
		(CompilerGrammarParser::ExprContext *ctx);
	antlrcpp::Any visitExprLogical
		(CompilerGrammarParser::ExprLogicalContext *ctx);
	antlrcpp::Any visitExprCompare
		(CompilerGrammarParser::ExprCompareContext *ctx);
	antlrcpp::Any visitExprAddSub
		(CompilerGrammarParser::ExprAddSubContext *ctx);
	antlrcpp::Any visitExprMulDivModEtc
		(CompilerGrammarParser::ExprMulDivModEtcContext *ctx);
	antlrcpp::Any visitExprUnary
		(CompilerGrammarParser::ExprUnaryContext *ctx);
	antlrcpp::Any visitExprCall
		(CompilerGrammarParser::ExprCallContext *ctx);
	antlrcpp::Any visitExprBitNot
		(CompilerGrammarParser::ExprBitNotContext *ctx);
	antlrcpp::Any visitExprLogNot
		(CompilerGrammarParser::ExprLogNotContext *ctx);
	antlrcpp::Any visitExprNegate
		(CompilerGrammarParser::ExprNegateContext *ctx);
	antlrcpp::Any visitListExpr
		(CompilerGrammarParser::ListExprContext *ctx);
	antlrcpp::Any visitNumExpr
		(CompilerGrammarParser::NumExprContext *ctx);
	antlrcpp::Any visitIdentExpr
		(CompilerGrammarParser::IdentExprContext *ctx);

private:		// functions

};



} // end namespace cake_plus_plus


#endif		// src_compiler_class_hpp
