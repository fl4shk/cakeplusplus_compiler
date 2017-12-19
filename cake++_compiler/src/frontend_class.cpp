#include "frontend_class.hpp"
#include "allocation_stuff.hpp"


FrntErrorListener::~FrntErrorListener()
{
}

void FrntErrorListener::syntaxError(antlr4::Recognizer *recognizer, 
	antlr4::Token *offendingSymbol, size_t line, 
	size_t charPositionInLine, const std::string &msg, 
	std::exception_ptr e)
{
	err("Syntax error on line ", line, 
		", position ", charPositionInLine, 
		":  ", msg, "\n");
}
void FrntErrorListener::reportAmbiguity(antlr4::Parser *recognizer, 
	const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, 
	bool exact, const antlrcpp::BitSet &ambigAlts, 
	antlr4::atn::ATNConfigSet *configs)
{
}

void FrntErrorListener::reportAttemptingFullContext
	(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, 
	size_t startIndex, size_t stopIndex,
	const antlrcpp::BitSet &conflictingAlts, 
	antlr4::atn::ATNConfigSet *configs)
{
}

void FrntErrorListener::reportContextSensitivity
	(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, 
	size_t startIndex, size_t stopIndex, size_t prediction, 
	antlr4::atn::ATNConfigSet *configs)
{
}

Frontend::~Frontend()
{
}

antlrcpp::Any Frontend::visitProgram
	(GrammarParser::ProgramContext *ctx)
{
//	//__program_node = mk_ast_node(AstOp::Prog);
//
//	{
//	auto&& funcDecl = ctx->funcDecl();
//
//	for (auto* decl : funcDecl)
//	{
//		decl->
//		if (__func_tbl.contains(decl->ident))
//		{
//			err(sconcat("cannot have more than one function called \"",
//				*decl->ident, "\"!"));
//		}
//
//		{
//		Function to_insert_or_assign(decl->ident);
//		__func_tbl.insert_or_assign(std::move(to_insert_or_assign));
//		}
//
//		__curr_func = &__func_tbl.at(decl->ident);
//
//		auto to_push = curr_func().append_vm_code();
//		//decl->accept(this);
//
//
//		//__program_node->append_child(pop_ast_node());
//	}
//	}
//
	return nullptr;
}

antlrcpp::Any Frontend::visitFuncDecl
	(GrammarParser::FuncDeclContext *ctx)
{
//	auto to_push = mk_ast_node(AstOp::FuncDecl);
//
//	ctx->identName()->accept(this);
//	to_push->ident = pop_str();
//
//	{
//	auto&& funcArgDecl = ctx->funcArgDecl();
//
//	for (auto func_arg_decl : funcArgDecl)
//	{
//		func_arg_decl->accept(this);
//		to_push->append_child(pop_ast_node());
//	}
//	}
//	ctx->statements()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitFuncCall
	(GrammarParser::FuncCallContext *ctx)
{
//	auto to_push = mk_ast_expr(AstExprOp::FuncCall);
//
//	ctx->identName()->accept(this);
//	to_push->ident = pop_str();
//
//	{
//	auto&& funcArgExpr = ctx->funcArgExpr();
//
//	for (auto func_arg_expr : funcArgExpr)
//	{
//		func_arg_expr->accept(this);
//		to_push->append_child(pop_ast_node());
//	}
//
//	}
//
//
//	push_ast_node(to_push);
	return nullptr;
}

antlrcpp::Any Frontend::visitFuncArgExpr
	(GrammarParser::FuncArgExprContext *ctx)
{
//	auto to_push = mk_ast_node(AstOp::FuncArgExpr);
//
//	ctx->identName()->accept(this);
//	to_push->ident = pop_str();
//
//
//	push_ast_node(to_push);
	return nullptr;
}

antlrcpp::Any Frontend::visitStatements
	(GrammarParser::StatementsContext *ctx)
{
//	auto to_push = mk_ast_stmt(AstStmtOp::List);
//
//	{
//	auto&& stmt = ctx->stmt();
//
//	for (auto iter : stmt)
//	{
//		iter->accept(this);
//	}
//
//	}
//
//	push_ast_node(to_push);
	return nullptr;
}


antlrcpp::Any Frontend::visitStmt
	(GrammarParser::StmtContext *ctx)
{
//	if (ctx->statements())
//	{
//		ctx->statements()->accept(this);
//	}
//	else if (ctx->varDecl())
//	{
//		ctx->varDecl()->accept(this);
//	}
//	//else if (ctx->expr())
//	//{
//	//	ctx->expr()->accept(this);
//	//}
//	else if (ctx->exprMulDivModEtc())
//	{
//		ctx->exprMulDivModEtc()->accept(this);
//	}
//	else if (ctx->assignment())
//	{
//		ctx->assignment()->accept(this);
//	}
//	else if (ctx->ifStatement())
//	{
//		ctx->ifStatement()->accept(this);
//	}
//	else if (ctx->ifChainStatement())
//	{
//		ctx->ifChainStatement()->accept(this);
//	}
//	else if (ctx->whileStatement())
//	{
//		ctx->whileStatement()->accept(this);
//	}
//	else if (ctx->doWhileStatement())
//	{
//		ctx->doWhileStatement()->accept(this);
//	}
//	else if (ctx->returnExprStatement())
//	{
//		ctx->returnExprStatement()->accept(this);
//	}
//	else if (ctx->returnNothingStatement())
//	{
//		ctx->returnNothingStatement()->accept(this);
//	}
//	else
//	{
//		err("visitStmt():  Eek!\n");
//	}
//
	return nullptr;
}

antlrcpp::Any Frontend::visitVarDecl
	(GrammarParser::VarDeclContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_var_decl);
//	auto to_push = mk_ast_stmt(AstStmtOp::VarDecl);
//	ctx->builtinTypename()->accept(this);
//	to_push->builtin_typename = pop_builtin_typename();
//
//	{
//
//	auto&& identDecl = ctx->identDecl();
//
//	for (auto ident_decl : identDecl)
//	{
//		ident_decl->accept(this);
//		to_push->append_child(pop_ast_node());
//	}
//
//	}
//
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitFuncArgDecl
	(GrammarParser::FuncArgDeclContext *ctx)
{
//	//auto to_push = mk_ast_node();
//	auto to_push = mk_ast_node(AstOp::FuncArgDecl);
//	ctx->builtinTypename()->accept(this);
//	to_push->builtin_typename = pop_builtin_typename();
//	
//	if (ctx->identName())
//	{
//		//to_push->op = AstOp::func_arg_decl_scalar;
//		to_push->func_arg_decl_op = AstFuncArgDeclOp::Scalar;
//		ctx->identName()->accept(this);
//	}
//	else if (ctx->nonSizedArrayIdentName())
//	{
//		//to_push->op = AstOp::func_arg_decl_arr;
//		to_push->func_arg_decl_op = AstFuncArgDeclOp::Arr;
//		ctx->nonSizedArrayIdentName()->accept(this);
//	}
//	else
//	{
//		err("visitFuncArgDecl():  Eek!\n");
//	}
//	to_push->ident = pop_str();
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitBuiltinTypename
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

antlrcpp::Any Frontend::visitNonSizedArrayIdentName
	(GrammarParser::NonSizedArrayIdentNameContext *ctx)
{
	ctx->identName()->accept(this);
	return nullptr;
}
antlrcpp::Any Frontend::visitAssignment
	(GrammarParser::AssignmentContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_assignment);
//	auto to_push = mk_ast_stmt(AstStmtOp::Assignment);
//
//	ctx->identExpr()->accept(this);
//	to_push->append_child(pop_ast_node());
//	ctx->expr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitIfStatement
	(GrammarParser::IfStatementContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_if);
//	auto to_push = mk_ast_stmt(AstStmtOp::If);
//
//	ctx->expr()->accept(this);
//	to_push->append_child(pop_ast_node());
//	ctx->statements()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitIfChainStatement
	(GrammarParser::IfChainStatementContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_if_chain);
//	auto to_push = mk_ast_stmt(AstStmtOp::IfChain);
//
//	ctx->expr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	ctx->statements()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	ctx->elseStatements()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitElseStatements
	(GrammarParser::ElseStatementsContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::list_stmts_else);
//	auto to_push = mk_ast_stmt(AstStmtOp::ListStmtsElse);
//
//	if (ctx->ifChainStatement())
//	{
//		ctx->ifChainStatement()->accept(this);
//	}
//	else if (ctx->statements())
//	{
//		ctx->statements()->accept(this);
//	}
//	else
//	{
//		err("visitElseStatements():  Eek!\n");
//	}
//
//	to_push->append_child(pop_ast_node());
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitWhileStatement
	(GrammarParser::WhileStatementContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_while);
//	auto to_push = mk_ast_stmt(AstStmtOp::While);
//
//	ctx->expr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	ctx->statements()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitDoWhileStatement
	(GrammarParser::DoWhileStatementContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_do_while);
//	auto to_push = mk_ast_stmt(AstStmtOp::DoWhile);
//
//	ctx->statements()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	ctx->expr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitReturnExprStatement
	(GrammarParser::ReturnExprStatementContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_return_expr);
//	auto to_push = mk_ast_stmt(AstStmtOp::ReturnExpr);
//
//	ctx->expr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitReturnNothingStatement
	(GrammarParser::ReturnNothingStatementContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_return_nothing);
//	auto to_push = mk_ast_stmt(AstStmtOp::ReturnNothing);
//
//	push_ast_node(to_push);
	return nullptr;
}

antlrcpp::Any Frontend::visitExpr
	(GrammarParser::ExprContext *ctx)
{
//	//if (ctx->exprLogical())
//	if (!ctx->expr())
//	{
//		ctx->exprLogical()->accept(this);
//	}
//	else if (ctx->expr())
//	{
//		//auto to_push = mk_ast_node(AstOp::expr_binop);
//		auto to_push = mk_ast_expr(AstExprOp::Binop);
//
//
//		ctx->expr()->accept(this);
//		to_push->append_child(pop_ast_node());
//
//		auto&& op = ctx->TokOpLogical()->toString();
//
//		if (op == "&&")
//		{
//			to_push->bin_op = AstBinOp::LogAnd;
//		}
//		else if (op == "||")
//		{
//			to_push->bin_op = AstBinOp::LogOr;
//		}
//		else
//		{
//			err("visitExpr():  binop type Eek!\n");
//		}
//
//		ctx->exprLogical()->accept(this);
//		to_push->append_child(pop_ast_node());
//		push_ast_node(to_push);
//	}
//	else
//	{
//		err("visitExpr():  Eek!\n");
//	}
//
	return nullptr;
}
antlrcpp::Any Frontend::visitExprLogical
	(GrammarParser::ExprLogicalContext *ctx)
{
//	//if (ctx->exprCompare())
//	if (!ctx->exprLogical())
//	{
//		ctx->exprCompare()->accept(this);
//	}
//	else if (ctx->exprLogical())
//	{
//		//auto to_push = mk_ast_node(AstOp::expr_binop);
//		auto to_push = mk_ast_expr(AstExprOp::Binop);
//
//
//		ctx->exprLogical()->accept(this);
//		to_push->append_child(pop_ast_node());
//
//		auto&& op = ctx->TokOpCompare()->toString();
//
//		if (op == "==")
//		{
//			to_push->bin_op = AstBinOp::CmpEq;
//		}
//		else if (op == "!=")
//		{
//			to_push->bin_op = AstBinOp::CmpNe;
//		}
//		else if (op == "<")
//		{
//			// Temporary!
//			to_push->bin_op = AstBinOp::CmpSLt;
//		}
//		else if (op == ">")
//		{
//			// Temporary
//			to_push->bin_op = AstBinOp::CmpSGt;
//		}
//		else if (op == "<=")
//		{
//			// Temporary!
//			to_push->bin_op = AstBinOp::CmpSLe;
//		}
//		else if (op == ">=")
//		{
//			// Temporary
//			to_push->bin_op = AstBinOp::CmpSGe;
//		}
//		else
//		{
//			err("visitExprLogical():  binop type Eek!\n");
//		}
//
//		ctx->exprCompare()->accept(this);
//		to_push->append_child(pop_ast_node());
//		push_ast_node(to_push);
//	}
//	else
//	{
//		err("visitExprCompare():  Eek!\n");
//	}
//
	return nullptr;
}
antlrcpp::Any Frontend::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
//	//if (ctx->exprAddSub())
//	if (!ctx->exprCompare())
//	{
//		ctx->exprAddSub()->accept(this);
//	}
//	else if (ctx->exprCompare())
//	{
//		//auto to_push = mk_ast_node(AstOp::expr_binop);
//		auto to_push = mk_ast_expr(AstExprOp::Binop);
//
//
//		ctx->exprCompare()->accept(this);
//		to_push->append_child(pop_ast_node());
//
//		auto&& op = ctx->TokOpAddSub()->toString();
//
//		if (op == "+")
//		{
//			to_push->bin_op = AstBinOp::Add;
//		}
//		else if (op == "-")
//		{
//			to_push->bin_op = AstBinOp::Sub;
//		}
//		else
//		{
//			err("visitExprCompare():  binop type Eek!\n");
//		}
//
//		ctx->exprAddSub()->accept(this);
//		to_push->append_child(pop_ast_node());
//		push_ast_node(to_push);
//	}
//	else
//	{
//		err("visitExprCompare():  Eek!\n");
//	}
//
	return nullptr;
}
antlrcpp::Any Frontend::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
//	//if (ctx->exprMulDivModEtc())
//	if (!ctx->exprAddSub())
//	{
//		ctx->exprMulDivModEtc()->accept(this);
//	}
//	else if (ctx->exprAddSub())
//	{
//		//auto to_push = mk_ast_node(AstOp::expr_binop);
//		auto to_push = mk_ast_expr(AstExprOp::Binop);
//
//
//		ctx->exprAddSub()->accept(this);
//		to_push->append_child(pop_ast_node());
//
//		std::string op;
//		
//		if (ctx->TokOpMulDivMod())
//		{
//			op = ctx->TokOpMulDivMod()->toString();
//		}
//		else if (ctx->TokOpBitwise())
//		{
//			op = ctx->TokOpBitwise()->toString();
//		}
//		else
//		{
//			err("visitExprAddSub():  operator Eek!\n");
//		}
//
//		if (op == "*")
//		{
//			to_push->bin_op = AstBinOp::Mul;
//		}
//		else if (op == "/")
//		{
//			// Temporary!
//			to_push->bin_op = AstBinOp::SDiv;
//		}
//		else if (op == "%")
//		{
//			// Temporary!
//			to_push->bin_op = AstBinOp::SMod;
//		}
//		else if (op == "&")
//		{
//			to_push->bin_op = AstBinOp::BitAnd;
//		}
//		else if (op == "|")
//		{
//			to_push->bin_op = AstBinOp::BitOr;
//		}
//		else if (op == "^")
//		{
//			to_push->bin_op = AstBinOp::BitXor;
//		}
//		else if (op == "<<")
//		{
//			to_push->bin_op = AstBinOp::BitLsl;
//		}
//		else if (op == ">>")
//		{
//			to_push->bin_op = AstBinOp::BitLsr;
//		}
//		else if (op == ">>>")
//		{
//			to_push->bin_op = AstBinOp::BitAsr;
//		}
//		else
//		{
//			err("visitExprAddSub():  binop type Eek!\n");
//		}
//
//		ctx->exprMulDivModEtc()->accept(this);
//		to_push->append_child(pop_ast_node());
//		push_ast_node(to_push);
//	}
//	else
//	{
//		err("visitExprAddSub():  Eek!\n");
//	}
//
	return nullptr;
}
antlrcpp::Any Frontend::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
{
//	if (ctx->exprUnary())
//	{
//		ctx->exprUnary()->accept(this);
//	}
//	else if (ctx->numExpr())
//	{
//		ctx->numExpr()->accept(this);
//	}
//	else if (ctx->funcCall())
//	{
//		ctx->funcCall()->accept(this);
//	}
//	else if (ctx->identExpr())
//	{
//		ctx->identExpr()->accept(this);
//	}
//	else if (ctx->lenExpr())
//	{
//		ctx->lenExpr()->accept(this);
//	}
//	else if (ctx->sizeofExpr())
//	{
//		ctx->sizeofExpr()->accept(this);
//	}
//	else if (ctx->expr())
//	{
//		ctx->expr()->accept(this);
//	}
//	else
//	{
//		err("visitExprMulDivModEtc():  Eek!\n");
//	}
	return nullptr;
}

antlrcpp::Any Frontend::visitExprUnary
	(GrammarParser::ExprUnaryContext *ctx)
{
//	if (ctx->exprBitInvert())
//	{
//		ctx->exprBitInvert()->accept(this);
//	}
//	else if (ctx->exprNegate())
//	{
//		ctx->exprNegate()->accept(this);
//	}
//	else if (ctx->exprLogNot())
//	{
//		ctx->exprLogNot()->accept(this);
//	}
//	else
//	{
//		printerr("visitExprUnary():  Eek!\n");
//	}
	return nullptr;
}
antlrcpp::Any Frontend::visitExprBitInvert
	(GrammarParser::ExprBitInvertContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::expr_unop);
//	auto to_push = mk_ast_expr(AstExprOp::Unop);
//	to_push->un_op = AstUnOp::BitInvert;
//
//	ctx->expr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitExprNegate
	(GrammarParser::ExprNegateContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::expr_unop);
//	auto to_push = mk_ast_expr(AstExprOp::Unop);
//	to_push->un_op = AstUnOp::Negate;
//
//	ctx->expr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitExprLogNot
	(GrammarParser::ExprLogNotContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::expr_unop);
//	auto to_push = mk_ast_expr(AstExprOp::Unop);
//	to_push->un_op = AstUnOp::LogNot;
//
//	ctx->expr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}


antlrcpp::Any Frontend::visitIdentExpr
	(GrammarParser::IdentExprContext *ctx)
{
//	//auto to_push = mk_ast_node();
//	auto to_push = mk_ast_node(AstOp::Expr);
//	ctx->identName()->accept(this);
//	to_push->ident = pop_str();
//
//	if (!ctx->subscriptExpr())
//	{
//		//to_push->op = AstOp::expr_ident_scalar;
//		to_push->expr_op = AstExprOp::IdentScalar;
//	}
//	else // if (ctx->subscriptExpr())
//	{
//		//to_push->op = AstOp::expr_ident_arr_elem;
//		to_push->expr_op = AstExprOp::IdentArrElem;
//
//		ctx->subscriptExpr()->accept(this);
//		to_push->append_child(pop_ast_node());
//	}
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitIdentDecl
	(GrammarParser::IdentDeclContext *ctx)
{
//	//auto to_push = mk_ast_node();
//	auto to_push = mk_ast_node(AstOp::IdentDecl);
//	ctx->identName()->accept(this);
//	to_push->ident = pop_str();
//
//	if (!ctx->subscriptConst())
//	{
//		//to_push->op = AstOp::ident_decl_scalar;
//		to_push->ident_decl_op = AstIdentDeclOp::Scalar;
//	}
//	else // if (ctx->subscriptConst())
//	{
//		//to_push->op = AstOp::ident_decl_arr;
//		to_push->ident_decl_op = AstIdentDeclOp::Arr;
//
//		ctx->subscriptConst()->accept(this);
//		to_push->append_child(pop_ast_node());
//	}
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitIdentName
	(GrammarParser::IdentNameContext *ctx)
{
	push_str(cstm_strdup(ctx->TokIdent()->toString()));
	return nullptr;
}

antlrcpp::Any Frontend::visitNumExpr
	(GrammarParser::NumExprContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::expr_constant);
//	auto to_push = mk_ast_expr(AstExprOp::Constant);
//
//
//	{
//	s64 temp;
//	std::stringstream sstm;
//	sstm << ctx->TokDecNum()->toString();
//	sstm >> temp;
//	to_push->num = temp;
//	}
//
//
//	push_ast_node(to_push);
	return nullptr;
}

antlrcpp::Any Frontend::visitLenExpr
	(GrammarParser::LenExprContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::expr_len);
//	auto to_push = mk_ast_expr(AstExprOp::Len);
//
//	ctx->identExpr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitSizeofExpr
	(GrammarParser::SizeofExprContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::expr_sizeof);
//	auto to_push = mk_ast_expr(AstExprOp::Sizeof);
//
//	ctx->identExpr()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	return nullptr;
}
antlrcpp::Any Frontend::visitSubscriptExpr
	(GrammarParser::SubscriptExprContext *ctx)
{
	ctx->expr()->accept(this);
	return nullptr;
}

antlrcpp::Any Frontend::visitSubscriptConst
	(GrammarParser::SubscriptConstContext *ctx)
{
	ctx->numExpr()->accept(this);
	return nullptr;
}