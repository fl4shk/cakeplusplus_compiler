#include "compiler_class.hpp"
#include "allocation_stuff.hpp"


CstmErrorListener::~CstmErrorListener()
{
}

void CstmErrorListener::syntaxError(antlr4::Recognizer *recognizer, 
	antlr4::Token *offendingSymbol, size_t line, 
	size_t charPositionInLine, const std::string &msg, 
	std::exception_ptr e)
{
	err("Syntax error on line ", line, 
		", position ", charPositionInLine, 
		":  ", msg, "\n");
}
void CstmErrorListener::reportAmbiguity(antlr4::Parser *recognizer, 
	const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, 
	bool exact, const antlrcpp::BitSet &ambigAlts, 
	antlr4::atn::ATNConfigSet *configs)
{
}

void CstmErrorListener::reportAttemptingFullContext
	(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, 
	size_t startIndex, size_t stopIndex,
	const antlrcpp::BitSet &conflictingAlts, 
	antlr4::atn::ATNConfigSet *configs)
{
}

void CstmErrorListener::reportContextSensitivity
	(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, 
	size_t startIndex, size_t stopIndex, size_t prediction, 
	antlr4::atn::ATNConfigSet *configs)
{
}

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

		if (pop_num())
		{
			to_push->append_child(pop_ast_node());
		}
	}

	}

	push_ast_node(to_push);
	return nullptr;
}

antlrcpp::Any Compiler::visitComment
	(GrammarParser::CommentContext *ctx)
{
	// Do nothing of interest here
	return nullptr;
}

antlrcpp::Any Compiler::visitStatement
	(GrammarParser::StatementContext *ctx)
{
	if (ctx->stmt())
	{
		ctx->stmt()->accept(this);

		// We don't need to push_ast_node() in this function

		// Signal to visitStatements() that there is an AstNode to append
		push_num(true);
	}
	else
	{
		// This is a comment of some variety
		push_num(false);
	}
	return nullptr;
}

antlrcpp::Any Compiler::visitStmt
	(GrammarParser::StmtContext *ctx)
{
	if (ctx->statements())
	{
		ctx->statements()->accept(this);
	}
	else if (ctx->varDecl())
	{
		ctx->varDecl()->accept(this);
	}
	else if (ctx->expr())
	{
		ctx->expr()->accept(this);
	}
	else if (ctx->assignment())
	{
		ctx->assignment()->accept(this);
	}
	else if (ctx->ifStatement())
	{
		ctx->ifStatement()->accept(this);
	}
	else if (ctx->ifChainStatement())
	{
		ctx->ifChainStatement()->accept(this);
	}
	else if (ctx->whileStatement())
	{
		ctx->whileStatement()->accept(this);
	}
	else if (ctx->doWhileStatement())
	{
		ctx->doWhileStatement()->accept(this);
	}
	else if (ctx->returnExprStatement())
	{
		ctx->returnExprStatement()->accept(this);
	}
	else if (ctx->returnNothingStatement())
	{
		ctx->returnNothingStatement()->accept(this);
	}
	else
	{
		err("visitStmt():  Eek!\n");
	}

	return nullptr;
}

antlrcpp::Any Compiler::visitVarDecl
	(GrammarParser::VarDeclContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::stmt_var_decl);
	ctx->builtinTypename()->accept(this);
	to_push->builtin_typename = pop_builtin_typename();

	{

	auto&& identDecl = ctx->identDecl();

	for (auto ident_decl : identDecl)
	{
		ident_decl->accept(this);
		to_push->append_child(pop_ast_node());
	}

	}


	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitFuncArgDecl
	(GrammarParser::FuncArgDeclContext *ctx)
{
	auto to_push = mk_ast_node();
	
	if (ctx->identName())
	{
		to_push->op = AstOp::func_arg_decl_scalar;
		ctx->identName()->accept(this);
	}
	else if (ctx->nonSizedArrayIdentName())
	{
		to_push->op = AstOp::func_arg_decl_arr;
		ctx->nonSizedArrayIdentName()->accept(this);
	}
	else
	{
		err("visitFuncArgDecl():  Eek!\n");
	}

	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitBuiltinTypename
	(GrammarParser::BuiltinTypenameContext *ctx)
{
	auto&& some_typename = ctx->TokBuiltinTypename()->toString();

	if (some_typename == "u64")
	{
		push_builtin_typename(BuiltinTypename::U64);
	}
	else if (some_typename == "s64")
	{
		push_builtin_typename(BuiltinTypename::S64);
	}
	else if (some_typename == "u32")
	{
		push_builtin_typename(BuiltinTypename::U32);
	}
	else if (some_typename == "s32")
	{
		push_builtin_typename(BuiltinTypename::S32);
	}
	else if (some_typename == "u16")
	{
		push_builtin_typename(BuiltinTypename::U16);
	}
	else if (some_typename == "s16")
	{
		push_builtin_typename(BuiltinTypename::S16);
	}
	else if (some_typename == "u8")
	{
		push_builtin_typename(BuiltinTypename::U8);
	}
	else if (some_typename == "s8")
	{
		push_builtin_typename(BuiltinTypename::S8);
	}
	else
	{
		err("visitBuiltinTypename():  Eek!\n");
	}
	return nullptr;
}

antlrcpp::Any Compiler::visitNonSizedArrayIdentName
	(GrammarParser::NonSizedArrayIdentNameContext *ctx)
{
	ctx->identName()->accept(this);
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
	s64 to_push;

	{
	std::stringstream sstm;
	sstm << ctx->TokDecNum()->toString();
	sstm >> to_push;
	}

	push_num(to_push);

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
