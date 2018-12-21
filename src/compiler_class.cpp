#include "compiler_class.hpp"

#include <sstream>



#define ANY_JUST_ACCEPT_BASIC(arg) \
	arg->accept(this)

#define ANY_ACCEPT_IF_BASIC(arg) \
	if (arg) \
	{ \
		ANY_JUST_ACCEPT_BASIC(arg); \
	}

#define ANY_PUSH_TOK_IF(arg) \
	if (arg) \
	{ \
		_push_str(unique_dup(arg->toString())); \
	}



namespace cake_plus_plus
{
Compiler::ParsePass operator + (Compiler::ParsePass some_parse_pass,
	size_t amount)
{
	size_t temp = static_cast<size_t>(some_parse_pass);
	temp += amount;
	return static_cast<Compiler::ParsePass>(temp);
}

Compiler::Compiler(CompilerGrammarParser& parser)
{
	_program_ctx = parser.program();
}

int Compiler::run()
{
	for (_parse_pass=static_cast<ParsePass>(0);
		_parse_pass<ParsePass::Lim;
		_parse_pass=_parse_pass+1)
	{
	}
	return 0;
}

antlrcpp::Any Compiler::visitProgram
	(CompilerGrammarParser::ProgramContext *ctx)
{
	ctx->listFunctions()->accept(this);

	return nullptr;
}
antlrcpp::Any Compiler::visitListFunctions
	(CompilerGrammarParser::ListFunctionsContext *ctx)
{
	auto&& function = ctx->function();

	for (auto func : function)
	{
		func->accept(this);
	}

	return nullptr;
}
antlrcpp::Any Compiler::visitFunction
	(CompilerGrammarParser::FunctionContext *ctx)
{
	return nullptr;
}


// Function args
antlrcpp::Any Compiler::visitListFunctionArgs
	(CompilerGrammarParser::ListFunctionArgsContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitFunctionArg
	(CompilerGrammarParser::FunctionArgContext *ctx)
{
	return nullptr;
}

// Statements
antlrcpp::Any Compiler::visitListStatements
	(CompilerGrammarParser::ListStatementsContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitStatement
	(CompilerGrammarParser::StatementContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitScopedStatements
	(CompilerGrammarParser::ScopedStatementsContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitStmtDeclVars
	(CompilerGrammarParser::StmtDeclVarsContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitStmtAssign
	(CompilerGrammarParser::StmtAssignContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitStmtIf
	(CompilerGrammarParser::StmtIfContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitStmtElse
	(CompilerGrammarParser::StmtElseContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitStmtWhile
	(CompilerGrammarParser::StmtWhileContext *ctx)
{
	return nullptr;
}

// Expressions
antlrcpp::Any Compiler::visitExpr
	(CompilerGrammarParser::ExprContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprLogical
	(CompilerGrammarParser::ExprLogicalContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprCompare
	(CompilerGrammarParser::ExprCompareContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprAddSub
	(CompilerGrammarParser::ExprAddSubContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprMulDivModEtc
	(CompilerGrammarParser::ExprMulDivModEtcContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprUnary
	(CompilerGrammarParser::ExprUnaryContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprCall
	(CompilerGrammarParser::ExprCallContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprBitNot
	(CompilerGrammarParser::ExprBitNotContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprLogNot
	(CompilerGrammarParser::ExprLogNotContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprNegate
	(CompilerGrammarParser::ExprNegateContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitListExpr
	(CompilerGrammarParser::ListExprContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitNumExpr
	(CompilerGrammarParser::NumExprContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitIdentExpr
	(CompilerGrammarParser::IdentExprContext *ctx)
{
	return nullptr;
}

} // end namespace cake_plus_plus
