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
	//else if (ctx->expr())
	//{
	//	ctx->expr()->accept(this);
	//}
	else if (ctx->exprMulDivModEtc())
	{
		ctx->exprMulDivModEtc()->accept(this);
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
	auto to_push = mk_ast_node(AstOp::stmt_assignment);

	ctx->identExpr()->accept(this);
	to_push->append_child(pop_ast_node());
	ctx->expr()->accept(this);
	to_push->append_child(pop_ast_node());

	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitIfStatement
	(GrammarParser::IfStatementContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::stmt_if);

	ctx->expr()->accept(this);
	to_push->append_child(pop_ast_node());
	ctx->statements()->accept(this);
	to_push->append_child(pop_ast_node());

	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitIfChainStatement
	(GrammarParser::IfChainStatementContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::stmt_if_chain);

	ctx->expr()->accept(this);
	to_push->append_child(pop_ast_node());

	ctx->statements()->accept(this);
	to_push->append_child(pop_ast_node());

	ctx->elseStatements()->accept(this);
	to_push->append_child(pop_ast_node());

	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitElseStatements
	(GrammarParser::ElseStatementsContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::list_stmts_else);

	if (ctx->ifChainStatement())
	{
		ctx->ifChainStatement()->accept(this);
	}
	else if (ctx->statements())
	{
		ctx->statements()->accept(this);
	}
	else
	{
		err("visitElseStatements():  Eek!\n");
	}

	to_push->append_child(pop_ast_node());
	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitWhileStatement
	(GrammarParser::WhileStatementContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::stmt_while);

	ctx->expr()->accept(this);
	to_push->append_child(pop_ast_node());

	ctx->statements()->accept(this);
	to_push->append_child(pop_ast_node());

	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitDoWhileStatement
	(GrammarParser::DoWhileStatementContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::stmt_do_while);

	ctx->statements()->accept(this);
	to_push->append_child(pop_ast_node());

	ctx->expr()->accept(this);
	to_push->append_child(pop_ast_node());

	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitReturnExprStatement
	(GrammarParser::ReturnExprStatementContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::stmt_return_expr);

	ctx->expr()->accept(this);
	to_push->append_child(pop_ast_node());

	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Compiler::visitReturnNothingStatement
	(GrammarParser::ReturnNothingStatementContext *ctx)
{
	auto to_push = mk_ast_node(AstOp::stmt_return_nothing);

	push_ast_node(to_push);
	return nullptr;
}

antlrcpp::Any Compiler::visitExpr
	(GrammarParser::ExprContext *ctx)
{
	if (ctx->exprLogical())
	{
		ctx->exprLogical()->accept(this);
	}
	else if (ctx->expr())
	{
		auto to_push = mk_ast_node(AstOp::expr_binop);


		ctx->expr()->accept(this);
		to_push->append_child(pop_ast_node());

		auto&& op = ctx->TokOpLogical()->toString();

		if (op == "&&")
		{
			to_push->bin_op = AstBinOp::LogAnd;
		}
		else if (op == "||")
		{
			to_push->bin_op = AstBinOp::LogOr;
		}
		else
		{
			err("visitExpr():  binop type Eek!\n");
		}

		ctx->exprLogical()->accept(this);
		to_push->append_child(pop_ast_node());
		push_ast_node(to_push);
	}
	else
	{
		err("visitExpr():  Eek!\n");
	}

	return nullptr;
}
antlrcpp::Any Compiler::visitExprLogical
	(GrammarParser::ExprLogicalContext *ctx)
{
	if (ctx->exprCompare())
	{
		ctx->exprCompare()->accept(this);
	}
	else if (ctx->exprLogical())
	{
		auto to_push = mk_ast_node(AstOp::expr_binop);


		ctx->exprLogical()->accept(this);
		to_push->append_child(pop_ast_node());

		auto&& op = ctx->TokOpCompare()->toString();

		if (op == "==")
		{
			to_push->bin_op = AstBinOp::CmpEq;
		}
		else if (op == "!=")
		{
			to_push->bin_op = AstBinOp::CmpNe;
		}
		else if (op == "<")
		{
			// Temporary!
			to_push->bin_op = AstBinOp::CmpSLt;
		}
		else if (op == ">")
		{
			// Temporary
			to_push->bin_op = AstBinOp::CmpSGt;
		}
		else if (op == "<=")
		{
			// Temporary!
			to_push->bin_op = AstBinOp::CmpSLe;
		}
		else if (op == ">=")
		{
			// Temporary
			to_push->bin_op = AstBinOp::CmpSGe;
		}
		else
		{
			err("visitExprLogical():  binop type Eek!\n");
		}

		ctx->exprCompare()->accept(this);
		to_push->append_child(pop_ast_node());
		push_ast_node(to_push);
	}
	else
	{
		err("visitExprCompare():  Eek!\n");
	}

	return nullptr;
}
antlrcpp::Any Compiler::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
	if (ctx->exprAddSub())
	{
		ctx->exprAddSub()->accept(this);
	}
	else if (ctx->exprCompare())
	{
		auto to_push = mk_ast_node(AstOp::expr_binop);


		ctx->exprCompare()->accept(this);
		to_push->append_child(pop_ast_node());

		auto&& op = ctx->TokOpAddSub()->toString();

		if (op == "+")
		{
			to_push->bin_op = AstBinOp::Add;
		}
		else if (op == "-")
		{
			to_push->bin_op = AstBinOp::Sub;
		}
		else
		{
			err("visitExprCompare():  binop type Eek!\n");
		}

		ctx->exprAddSub()->accept(this);
		to_push->append_child(pop_ast_node());
		push_ast_node(to_push);
	}
	else
	{
		err("visitExprCompare():  Eek!\n");
	}

	return nullptr;
}
antlrcpp::Any Compiler::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
	if (ctx->exprMulDivModEtc())
	{
		ctx->exprMulDivModEtc()->accept(this);
	}
	else if (ctx->exprAddSub())
	{
		auto to_push = mk_ast_node(AstOp::expr_binop);


		ctx->exprAddSub()->accept(this);
		to_push->append_child(pop_ast_node());

		std::string op;
		
		if (ctx->TokOpMulDivMod())
		{
			op = ctx->TokOpMulDivMod()->toString();
		}
		else if (ctx->TokOpBitwise())
		{
			op = ctx->TokOpBitwise()->toString();
		}
		else
		{
			err("visitExprAddSub():  operator Eek!\n");
		}

		if (op == "*")
		{
			to_push->bin_op = AstBinOp::Mul;
		}
		else if (op == "/")
		{
			// Temporary!
			to_push->bin_op = AstBinOp::SDiv;
		}
		else if (op == "%")
		{
			// Temporary!
			to_push->bin_op = AstBinOp::SMod;
		}
		else if (op == "&")
		{
			to_push->bin_op = AstBinOp::BitAnd;
		}
		else if (op == "|")
		{
			to_push->bin_op = AstBinOp::BitOr;
		}
		else if (op == "^")
		{
			to_push->bin_op = AstBinOp::BitXor;
		}
		else if (op == "<<")
		{
			to_push->bin_op = AstBinOp::BitLsl;
		}
		else if (op == ">>")
		{
			to_push->bin_op = AstBinOp::BitLsr;
		}
		else if (op == ">>>")
		{
			to_push->bin_op = AstBinOp::BitAsr;
		}
		else
		{
			err("visitExprAddSub():  binop type Eek!\n");
		}

		ctx->exprMulDivModEtc()->accept(this);
		to_push->append_child(pop_ast_node());
		push_ast_node(to_push);
	}
	else
	{
		err("visitExprAddSub():  Eek!\n");
	}

	return nullptr;
}
antlrcpp::Any Compiler::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
{
	if (ctx->exprUnary())
	{
		ctx->exprUnary()->accept(this);
	}
	else if (ctx->numExpr())
	{
		ctx->numExpr()->accept(this);
	}
	else if (ctx->funcCall())
	{
		ctx->funcCall()->accept(this);
	}
	else if (ctx->identExpr())
	{
		ctx->identExpr()->accept(this);
	}
	else if (ctx->lenExpr())
	{
		ctx->lenExpr()->accept(this);
	}
	else if (ctx->sizeofExpr())
	{
		ctx->sizeofExpr()->accept(this);
	}
	else if (ctx->expr())
	{
		ctx->expr()->accept(this);
	}
	else
	{
		err("visitExprMulDivModEtc():  Eek!\n");
	}
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
