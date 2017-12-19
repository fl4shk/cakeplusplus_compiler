#include "compiler_class.hpp"
#include "allocation_stuff.hpp"

Compiler::~Compiler()
{
}

antlrcpp::Any Compiler::visitProgram
	(GrammarParser::ProgramContext *ctx)
{
	__program_node = mk_ast_node(AstOp::prog);

	{
	auto&& funcDecl = ctx->funcDecl();

	for (auto* decl : funcDecl)
	{
		decl->accept(this);
		__program_node->append_child(pop_ast_node());
	}
	}

	return nullptr;
}

antlrcpp::Any Compiler::visitFuncDecl
	(GrammarParser::FuncDeclContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::func_decl);

	ctx->identName()->accept(this);
	to_push->ident = pop_str();

	{
	auto&& funcArgDecl = ctx->funcArgDecl();

	for (auto func_arg_decl : funcArgDecl)
	{
		func_arg_decl->accept(this);
		to_push->append_child(pop_ast_node());
	}
	}
	ctx->statements()->accept(this);
	to_push->append_child(pop_ast_node());


	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitFuncCall
	(GrammarParser::FuncCallContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::func_call);

	ctx->identName()->accept(this);
	to_push->ident = pop_str();

	{
	auto&& funcArgExpr = ctx->funcArgExpr();

	for (auto func_arg_expr : funcArgExpr)
	{
		func_arg_expr->accept(this);
		to_push->append_child(pop_ast_node());
	}

	}


	push_ast_node(to_push);
	return nullptr;
}

antlrcpp::Any Compiler::visitFuncArgExpr
	(GrammarParser::FuncArgExprContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::func_arg_expr);

	ctx->identName()->accept(this);
	to_push->ident = pop_str();


	push_ast_node(to_push);
	return nullptr;
}

antlrcpp::Any Compiler::visitStatements
	(GrammarParser::StatementsContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::list_stmts);

	{
	auto&& statement = ctx->statement();

	for (auto stmt : statement)
	{
		stmt->accept(this);
		to_push->append_child(pop_ast_node());
	}

	}

	push_ast_node(to_push);
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
antlrcpp::Any Compiler::visitFuncArgDecl
	(GrammarParser::FuncArgDeclContext *ctx)
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
antlrcpp::Any Compiler::visitReturnExprStatement
	(GrammarParser::ReturnExprStatementContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Compiler::visitReturnNothingStatement
	(GrammarParser::ReturnNothingStatementContext *ctx)
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
