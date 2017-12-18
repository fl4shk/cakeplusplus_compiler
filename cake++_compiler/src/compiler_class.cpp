#include "compiler_class.hpp"
#include "allocation_stuff.hpp"

Compiler::~Compiler()
{
}

antlrcpp::Any Compiler::visitProgram
	(GrammarParser::ProgramContext *ctx)
{
	auto&& funcDecl = ctx->funcDecl();

	for (auto* decl : funcDecl)
	{
		decl->accept(this);
	}

	return nullptr;
}

antlrcpp::Any Compiler::visitFuncDecl
	(GrammarParser::FuncDeclContext *ctx)
{
	ctx->identName()->accept(this);
	auto ident = pop_str();

	printout("I found this function:  ", *ident, "\n");

	auto&& funcVarDecl = ctx->funcVarDecl();

	return nullptr;
}
antlrcpp::Any Compiler::visitFuncCall
	(GrammarParser::FuncCallContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Compiler::visitFuncArgExpr
	(GrammarParser::FuncArgExprContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Compiler::visitStatements
	(GrammarParser::StatementsContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Compiler::visitStatement
	(GrammarParser::StatementContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Compiler::visitVarDecl
	(GrammarParser::VarDeclContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitFuncVarDecl
	(GrammarParser::FuncVarDeclContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitBuiltinTypename
	(GrammarParser::BuiltinTypenameContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Compiler::visitNonSizedArrayIdentName
	(GrammarParser::NonSizedArrayIdentNameContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitAssignment
	(GrammarParser::AssignmentContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitIfStatement
	(GrammarParser::IfStatementContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitIfChainStatement
	(GrammarParser::IfChainStatementContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitElseStatements
	(GrammarParser::ElseStatementsContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitWhileStatement
	(GrammarParser::WhileStatementContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitDoWhileStatement
	(GrammarParser::DoWhileStatementContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Compiler::visitExpr
	(GrammarParser::ExprContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprLogical
	(GrammarParser::ExprLogicalContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Compiler::visitExprUnary
	(GrammarParser::ExprUnaryContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprBitInvert
	(GrammarParser::ExprBitInvertContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprNegate
	(GrammarParser::ExprNegateContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitExprLogNot
	(GrammarParser::ExprLogNotContext *ctx)
{
	return nullptr;
}


antlrcpp::Any Compiler::visitIdentExpr
	(GrammarParser::IdentExprContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitIdentDecl
	(GrammarParser::IdentDeclContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitIdentName
	(GrammarParser::IdentNameContext *ctx)
{
	push_str(cstm_strdup(ctx->TokIdent()->toString()));
	return nullptr;
}

antlrcpp::Any Compiler::visitNumExpr
	(GrammarParser::NumExprContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Compiler::visitLenExpr
	(GrammarParser::LenExprContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitSizeofExpr
	(GrammarParser::SizeofExprContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitSubscriptExpr
	(GrammarParser::SubscriptExprContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Compiler::visitSubscriptConst
	(GrammarParser::SubscriptConstContext *ctx)
{
	return nullptr;
}
