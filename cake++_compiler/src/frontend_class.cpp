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
	//__program_node = mk_ast_node(AstOp::Prog);

	auto&& funcDecl = ctx->funcDecl();

	std::map<GrammarParser::FuncDeclContext*, Ident> temp_ident_map;

	for (auto* func_decl : funcDecl)
	{
		func_decl->identName()->accept(this);
		auto ident = pop_str();

		temp_ident_map[func_decl] = ident;

		if (__func_tbl.contains(ident))
		{
			err(sconcat("Can't have more than one function called \"",
				*ident, "\"!"));
		}

		__func_tbl.insert_or_assign(mkfunc(ident));

		__curr_func = __func_tbl.at(ident);

		auto&& funcArgDecl = func_decl->funcArgDecl();

		// Fill up the symbol table with the arguments to the function
		for (auto* func_arg_decl : funcArgDecl)
		{
			func_arg_decl->accept(this);
		}
	}

	// Now visit the statements
	for (auto* iter : funcDecl)
	{
		auto ident = temp_ident_map.at(iter);
		__curr_func = __func_tbl.at(ident);
		iter->accept(this);

		codegen().osprint_func(cout, curr_func());
	}

	return nullptr;
}

antlrcpp::Any Frontend::visitFuncDecl
	(GrammarParser::FuncDeclContext *ctx)
{
	// Just do the statements stuff here
	ctx->statements()->accept(this);

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


	ctx->identName()->accept(this);
	auto ident = pop_str();

	Function* func;
	{
	func = __func_tbl.at(ident);
	}

	if (func == nullptr)
	{
		err(sconcat("Can't find function with identifier \"", *ident, 
			"\"!"));
	}

	//auto to_push = mk_unlinked_ir_code(IrOp::Call);

	// here we are making an 
	auto to_push = codegen().mk_unfinished_call();


	// The first argument of a Call IrCode node is the address of whatever
	// function we're calling
	to_push->args.push_back(codegen().mk_address(func));

	{
	auto&& funcArgExpr = ctx->funcArgExpr();

	auto&& args = func->get_args();

	if (args.size() != funcArgExpr.size())
	{
		err(sconcat("Function called \"", *ident, "\" expects ",
			args.size(), " arguments, but instead got ",
			funcArgExpr.size(), " arguments!"));
	}

	//for (auto func_arg_expr : funcArgExpr)
	for (size_t i=0; i<funcArgExpr.size(); ++i)
	{
		push_func(func);
		push_num(i);
		push_sym(args.at(i));

		auto func_arg_expr = funcArgExpr.at(i);

		func_arg_expr->accept(this);
		to_push->args.push_back(pop_ir_code());
	}


	}


	// Necessary because codegen().mk_unfinished_call() doesn't perform
	// relink_ir_code().
	relink_ir_code(to_push);
	push_ir_code(to_push);

	return nullptr;
}

antlrcpp::Any Frontend::visitFuncArgExpr
	(GrammarParser::FuncArgExprContext *ctx)
{
	auto func = pop_func();
	const auto which_arg = pop_num();
	auto arg_sym = pop_sym();


	ctx->identName()->accept(this);
	auto ident = pop_str();

	auto sym = find_sym_or_err(ident,
		sconcat("No symbol exists called \"", *ident, "\"!"));

	// Function argument type checking
	if ((arg_sym->type() == SymType::ScalarVarName)
		&& (sym->type() != SymType::ScalarVarName))
	{
		err(sconcat("Function called \"", *func->name(),
			"\" expects a scalar value for argument number ",
			which_arg, "!"));
	}
	if (arg_sym->type() == SymType::ArrayVarName)
	{
		if (sym->type() != SymType::ArrayVarName)
		{
			err(sconcat("Function called \"", *func->name(),
				"\" expects an array value for argument number ",
				which_arg, "!"));
		}
		else if (sym->type() == SymType::ArrayVarName)
		{
			if (arg_sym->var_type() != sym->var_type())
			{
				err(sconcat("Function called \"", *func->name(),
					"\" expects an array of type ",
					arg_sym->var_type(), " for argument number ",
					which_arg, "!"));
			}
		}
		else
		{
			err("visitFuncArgExpr():  Argument type checking Eek!");
		}
	}

	if (sym->type() == SymType::ScalarVarName)
	{
		// Scalars are passed by value
		auto addr = codegen().mk_address(sym);
		auto index = codegen().mk_const(0);


		push_ir_code(codegen().mk_ldx(sym->get_unsgn_or_sgn(),
			sym->get_ldst_size(), addr, index));
	}
	else if (sym->type() == SymType::ArrayVarName)
	{
		// Since arrays are passed by reference, we only need to grab the
		// address for this argument
		push_ir_code(codegen().mk_address(sym));
	}
	else
	{
		err("visitFuncArgExpr():  Eek!\n");
	}

	return nullptr;
}

antlrcpp::Any Frontend::visitStatements
	(GrammarParser::StatementsContext *ctx)
{
	auto&& stmt = ctx->stmt();

	sym_tbl().mkscope();

	for (auto iter : stmt)
	{
		iter->accept(this);
	}

	sym_tbl().rmscope();

	return nullptr;
}


antlrcpp::Any Frontend::visitStmt
	(GrammarParser::StmtContext *ctx)
{
	if (ctx->statements())
	{
		ctx->statements()->accept(this);
	}
	else if (ctx->putnStatement())
	{
		ctx->putnStatement()->accept(this);
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

antlrcpp::Any Frontend::visitPutnStatement
	(GrammarParser::PutnStatementContext *ctx)
{
	ctx->expr()->accept(this);
	IrCode* expr = pop_ir_code();

	codegen().mk_syscall(IrSyscallShorthandOp::DispNum);

	codegen().mk_const('\n');
	codegen().mk_syscall(IrSyscallShorthandOp::DispChar);

	return nullptr;
}
antlrcpp::Any Frontend::visitVarDecl
	(GrammarParser::VarDeclContext *ctx)
{
	ctx->builtinTypename()->accept(this);
	const auto some_builtin_typename = pop_builtin_typename();

	auto&& identDecl = ctx->identDecl();

	for (auto iter : identDecl)
	{
		// Pushing some_builtin_typename every iteration is fine because
		// visitIdentDecl() performs pop_builtin_typename().
		push_builtin_typename(some_builtin_typename);
		iter->accept(this);
	}


	return nullptr;
}
antlrcpp::Any Frontend::visitFuncArgDecl
	(GrammarParser::FuncArgDeclContext *ctx)
{
	Symbol arg;
	ctx->builtinTypename()->accept(this);
	arg.set_var_type(pop_builtin_typename());

	if (ctx->identName())
	{
		ctx->identName()->accept(this);
		arg.set_type(SymType::ScalarVarName);
	}
	else if (ctx->nonSizedArrayIdentName())
	{
		ctx->nonSizedArrayIdentName()->accept(this);
		arg.set_type(SymType::ArrayVarName);
	}
	else
	{
		err("visitFuncArgDecl():  Eek!\n");
	}

	arg.set_name(pop_str());

	{
	auto sym = sym_tbl().find_in_first_blklev(arg.name());

	if (sym != nullptr)
	{
		err(sconcat("Function called \"", *curr_func().name(), 
			"\" cannot have two arguments with same identifiers!",
			"Note:  offending argument has identifier \"",
			*arg.name(), "\"."));
	}
	}

	// This is an argument
	arg.set_is_arg(true);

	// Which argument in the list is this? 
	++curr_func().last_arg_offset();
	arg.set_arg_offset(curr_func().last_arg_offset());

	sym_tbl().insert_or_assign(std::move(arg));

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
	ctx->identLhs()->accept(this);

	auto addr = pop_ir_code();
	auto index = pop_ir_code();

	ctx->expr()->accept(this);
	auto expr = pop_ir_code();

	auto sym = pop_sym();

	push_ir_code(codegen().mk_stx(sym->get_unsgn_or_sgn(),
		sym->get_ldst_size(), addr, index, expr));
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


	ctx->expr()->accept(this);
	auto expr = pop_ir_code();


	auto label_after_statements = codegen().mk_unlinked_label();

	codegen().mk_branch_if_false(label_after_statements, expr);

	ctx->statements()->accept(this);

	relink_ir_code(label_after_statements);

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

	ctx->expr()->accept(this);
	auto expr = pop_ir_code();

	auto label_after_statements = codegen().mk_unlinked_label();


	// Branch to the else stuff if false
	codegen().mk_branch_if_false(label_after_statements, expr);

	ctx->statements()->accept(this);



	auto label_after_else_statements = codegen().mk_unlinked_label();


	// Branch to the part that's after the elseStatements
	codegen().mk_bra(label_after_else_statements);

	relink_ir_code(label_after_statements);

	ctx->elseStatements()->accept(this);

	relink_ir_code(label_after_else_statements);



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
	

	if (ctx->ifStatement())
	{
		ctx->ifStatement()->accept(this);
	}
	else if (ctx->ifChainStatement())
	{
		ctx->ifChainStatement()->accept(this);
	}
	else if (ctx->statements())
	{
		ctx->statements()->accept(this);
	}

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

	auto label_before_expr = codegen().mk_label();

	ctx->expr()->accept(this);
	auto expr = pop_ir_code();


	auto label_after_while = codegen().mk_unlinked_label();
	codegen().mk_branch_if_false(label_after_while, expr);

	ctx->statements()->accept(this);


	// For a while loop, always branch back up to the label_before_expr if
	// we didn't conditionally end the loop.
	codegen().mk_bra(label_before_expr);

	relink_ir_code(label_after_while);


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

	auto label_before_statements = codegen().mk_label();

	ctx->statements()->accept(this);


	ctx->expr()->accept(this);
	auto expr = pop_ir_code();

	codegen().mk_bne(label_before_statements, expr);


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
	err("visitReturnExprStatement() is not fully implemented!");
	return nullptr;
}
antlrcpp::Any Frontend::visitReturnNothingStatement
	(GrammarParser::ReturnNothingStatementContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_return_nothing);
//	auto to_push = mk_ast_stmt(AstStmtOp::ReturnNothing);
//
//	push_ast_node(to_push);
	err("visitReturnNothingStatement() is not fully implemented!");
	return nullptr;
}

antlrcpp::Any Frontend::visitExpr
	(GrammarParser::ExprContext *ctx)
{
	//if (ctx->exprLogical())
	if (!ctx->expr())
	{
		ctx->exprLogical()->accept(this);
	}
	else if (ctx->expr())
	{
		////auto to_push = mk_ast_node(AstOp::expr_binop);
		//auto to_push = mk_ast_expr(AstExprOp::Binop);


		ctx->expr()->accept(this);
		auto a = pop_ir_code();
		//to_push->append_child(pop_ast_node());

		auto&& op = ctx->TokOpLogical()->toString();

		IrBinop s_binop;

		if (op == "&&")
		{
			//to_push->bin_op = AstBinOp::LogAnd;
			s_binop = IrBinop::BitAnd;
		}
		else if (op == "||")
		{
			//to_push->bin_op = AstBinOp::LogOr;
			s_binop = IrBinop::BitOr;
		}
		else
		{
			err("visitExpr():  binop type Eek!\n");
		}

		ctx->exprLogical()->accept(this);
		auto b = pop_ir_code();

		auto some_binop = codegen().mk_binop(s_binop, a, b);


		// ((a bitop b) != 0)
		push_ir_code(codegen().mk_log_not(some_binop));


		//to_push->append_child(pop_ast_node());
		//push_ast_node(to_push);
	}
	else
	{
		err("visitExpr():  Eek!\n");
	}

	return nullptr;
}
antlrcpp::Any Frontend::visitExprLogical
	(GrammarParser::ExprLogicalContext *ctx)
{
	//if (ctx->exprCompare())
	if (!ctx->exprLogical())
	{
		ctx->exprCompare()->accept(this);
	}
	else if (ctx->exprLogical())
	{
		////auto to_push = mk_ast_node(AstOp::expr_binop);
		//auto to_push = mk_ast_expr(AstExprOp::Binop);


		ctx->exprLogical()->accept(this);
		auto a = pop_ir_code();
		//to_push->append_child(pop_ast_node());

		auto&& op = ctx->TokOpCompare()->toString();


		IrCode* to_push;

		if (op == "==")
		{
			//to_push->bin_op = AstBinOp::CmpEq;
			ctx->exprCompare()->accept(this);
			auto b = pop_ir_code();

			to_push = codegen().mk_binop(IrBinop::CmpEq, a, b);
		}
		else if (op == "!=")
		{
			//to_push->bin_op = AstBinOp::CmpNe;
			ctx->exprCompare()->accept(this);
			auto b = pop_ir_code();

			to_push = codegen().mk_binop(IrBinop::CmpNe, a, b);
		}
		else if (op == "<")
		{
			// Temporary!
			//to_push->bin_op = AstBinOp::CmpSLt;
			ctx->exprCompare()->accept(this);
			auto b = pop_ir_code();

			to_push = codegen().mk_binop(IrBinop::CmpLt, a, b);
		}
		else if (op == ">")
		{
			// Temporary
			//to_push->bin_op = AstBinOp::CmpSGt;
			ctx->exprCompare()->accept(this);
			auto b = pop_ir_code();

			to_push = codegen().mk_log_not(codegen().mk_binop
				(IrBinop::CmpLe, a, b));
		}
		else if (op == "<=")
		{
			// Temporary!
			//to_push->bin_op = AstBinOp::CmpSLe;
			ctx->exprCompare()->accept(this);
			auto b = pop_ir_code();

			to_push = codegen().mk_binop(IrBinop::CmpLe, a, b);
		}
		else if (op == ">=")
		{
			// Temporary
			//to_push->bin_op = AstBinOp::CmpSGe;
			ctx->exprCompare()->accept(this);
			auto b = pop_ir_code();

			to_push = codegen().mk_log_not(codegen().mk_binop
				(IrBinop::CmpLt, a, b));
		}
		else
		{
			err("visitExprLogical():  binop type Eek!\n");
		}

		//to_push->append_child(pop_ast_node());
		//push_ast_node(to_push);

		push_ir_code(to_push);
	}
	else
	{
		err("visitExprCompare():  Eek!\n");
	}

	return nullptr;
}
antlrcpp::Any Frontend::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
	//if (ctx->exprAddSub())
	if (!ctx->exprCompare())
	{
		ctx->exprAddSub()->accept(this);
	}
	else if (ctx->exprCompare())
	{
		////auto to_push = mk_ast_node(AstOp::expr_binop);
		//auto to_push = mk_ast_expr(AstExprOp::Binop);


		ctx->exprCompare()->accept(this);
		auto a = pop_ir_code();

		//to_push->append_child(pop_ast_node());

		auto&& op = ctx->TokOpAddSub()->toString();

		IrBinop s_binop;

		if (op == "+")
		{
			//to_push->bin_op = AstBinOp::Add;
			s_binop = IrBinop::Add;
		}
		else if (op == "-")
		{
			//to_push->bin_op = AstBinOp::Sub;
			s_binop = IrBinop::Sub;
		}
		else
		{
			err("visitExprCompare():  binop type Eek!\n");
		}

		ctx->exprAddSub()->accept(this);
		auto b = pop_ir_code();
		//to_push->append_child(pop_ast_node());
		//push_ast_node(to_push);

		push_ir_code(codegen().mk_binop(s_binop, a, b));
	}
	else
	{
		err("visitExprCompare():  Eek!\n");
	}

	return nullptr;
}
antlrcpp::Any Frontend::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
	//if (ctx->exprMulDivModEtc())
	if (!ctx->exprAddSub())
	{
		ctx->exprMulDivModEtc()->accept(this);
	}
	else if (ctx->exprAddSub())
	{
		////auto to_push = mk_ast_node(AstOp::expr_binop);
		//auto to_push = mk_ast_expr(AstExprOp::Binop);


		ctx->exprAddSub()->accept(this);
		auto a = pop_ir_code();

		//to_push->append_child(pop_ast_node());

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

		IrBinop s_binop;

		if (op == "*")
		{
			//to_push->bin_op = AstBinOp::Mul;
			s_binop = IrBinop::Mul;
		}
		else if (op == "/")
		{
			// Temporary!
			//to_push->bin_op = AstBinOp::SDiv;
			s_binop = IrBinop::Div;
		}
		else if (op == "%")
		{
			// Temporary!
			//to_push->bin_op = AstBinOp::SMod;
			s_binop = IrBinop::Mod;
		}
		else if (op == "&")
		{
			//to_push->bin_op = AstBinOp::BitAnd;
			s_binop = IrBinop::BitAnd;
		}
		else if (op == "|")
		{
			//to_push->bin_op = AstBinOp::BitOr;
			s_binop = IrBinop::BitOr;
		}
		else if (op == "^")
		{
			//to_push->bin_op = AstBinOp::BitXor;
			s_binop = IrBinop::BitXor;
		}
		else if (op == "<<")
		{
			//to_push->bin_op = AstBinOp::BitLsl;
			s_binop = IrBinop::BitLsl;
		}
		else if (op == ">>")
		{
			//to_push->bin_op = AstBinOp::BitLsr;
			s_binop = IrBinop::BitLsr;
		}
		else if (op == ">>>")
		{
			//to_push->bin_op = AstBinOp::BitAsr;
			s_binop = IrBinop::BitAsr;
		}
		else
		{
			err("visitExprAddSub():  binop type Eek!\n");
		}

		ctx->exprMulDivModEtc()->accept(this);
		auto b = pop_ir_code();
		//to_push->append_child(pop_ast_node());
		//push_ast_node(to_push);

		push_ir_code(codegen().mk_binop(s_binop, a, b));
	}
	else
	{
		err("visitExprAddSub():  Eek!\n");
	}

	return nullptr;
}
antlrcpp::Any Frontend::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
{
	if (ctx->exprUnary())
	{
		ctx->exprUnary()->accept(this);
	}
	else if (ctx->numExpr())
	{
		ctx->numExpr()->accept(this);

		push_ir_code(codegen().mk_const(pop_num()));
	}
	else if (ctx->funcCall())
	{
		ctx->funcCall()->accept(this);
	}
	else if (ctx->identRhs())
	{
		ctx->identRhs()->accept(this);
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

antlrcpp::Any Frontend::visitExprUnary
	(GrammarParser::ExprUnaryContext *ctx)
{
	if (ctx->exprBitInvert())
	{
		ctx->exprBitInvert()->accept(this);
	}
	else if (ctx->exprNegate())
	{
		ctx->exprNegate()->accept(this);
	}
	else if (ctx->exprLogNot())
	{
		ctx->exprLogNot()->accept(this);
	}
	else
	{
		printerr("visitExprUnary():  Eek!\n");
	}
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
	ctx->expr()->accept(this);
	auto expr = pop_ir_code();

	auto negative_one = codegen().mk_const(-1);

	push_ir_code(codegen().mk_binop(IrBinop::BitXor, expr, negative_one));

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
	
	ctx->expr()->accept(this);
	auto expr = pop_ir_code();

	auto zero = codegen().mk_const(0);

	push_ir_code(codegen().mk_binop(IrBinop::Sub, zero, expr));

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
	
	ctx->expr()->accept(this);
	auto expr = pop_ir_code();

	push_ir_code(codegen().mk_log_not(expr));
	return nullptr;
}

void Frontend::__visit_ident_access
	(GrammarParser::IdentNameContext* ctx_ident_name,
	GrammarParser::SubscriptExprContext* ctx_subscript_expr)
{
	ctx_ident_name->accept(this);
	auto ident = pop_str();

	auto sym = find_sym_or_err(ident, 
		sconcat("No symbol with identifier \"", *ident, 
		"\" was found!"));

	auto addr = codegen().mk_address(sym);
	IrCode* index;

	
	if (sym->type() == SymType::ScalarVarName)
	{
		if (!ctx_subscript_expr)
		{
			index = codegen().mk_const(0);
		}
		else // if (ctx_subscript_expr)
		{
			err(sconcat("Symbol with identifier \"", *ident, 
				"\" is not an array!"));
		}
	}

	else if (sym->type() == SymType::ArrayVarName)
	{
		if (!ctx_subscript_expr)
		{
			err(sconcat("Symbol with identifier \"", *ident, 
				"\" is an array!"));
		}
		else // if (ctx_subscript_expr)
		{
			ctx_subscript_expr->accept(this);
			index = pop_ir_code();
		}
	}
	else
	{
		err("__visit_ident_access():  Unknown SymType!");
	}

	//push_ir_code(codegen().mk_ldx(addr, index));
	push_sym(sym);
	push_ir_code(index);
	push_ir_code(addr);
}

antlrcpp::Any Frontend::visitIdentLhs
	(GrammarParser::IdentLhsContext *ctx)
{
	__visit_ident_access(ctx->identName(), ctx->subscriptExpr());
	return nullptr;
}

antlrcpp::Any Frontend::visitIdentRhs
	(GrammarParser::IdentRhsContext *ctx)
{
	__visit_ident_access(ctx->identName(), ctx->subscriptExpr());

	auto addr = pop_ir_code();
	auto index = pop_ir_code();


	auto sym = pop_sym();


	push_ir_code(codegen().mk_ldx(sym->get_unsgn_or_sgn(), 
		sym->get_ldst_size(), addr, index));

	return nullptr;
}
antlrcpp::Any Frontend::visitIdentDecl
	(GrammarParser::IdentDeclContext *ctx)
{
	Symbol var;
	var.set_var_type(pop_builtin_typename());

	ctx->identName()->accept(this);
	var.set_name(pop_str());

	if (sym_tbl().find_in_this_blklev(var.name()) != nullptr)
	{
		err(sconcat("Symbol with identifier \"", *var.name(), 
			"\" already exists in this scope!\n"));
	}

	if (!ctx->subscriptConst())
	{
		var.set_type(SymType::ScalarVarName);
		var.set_size(1);
	}
	else // if (ctx->subscriptConst())
	{
		var.set_type(SymType::ArrayVarName);
		ctx->subscriptConst()->accept(this);
		var.set_size(pop_num());
	}

	var.set_is_arg(false);

	sym_tbl().insert_or_assign(std::move(var));


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
	s64 to_push;
	std::stringstream sstm;
	sstm << ctx->TokDecNum()->toString();
	sstm >> to_push;

	push_num(to_push);
	return nullptr;
}

antlrcpp::Any Frontend::visitLenExpr
	(GrammarParser::LenExprContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::expr_len);
//	auto to_push = mk_ast_expr(AstExprOp::Len);
//
//	ctx->identRhs()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);

	//err("visitLenExpr() is not fully implemented!");

	ctx->identName()->accept(this);

	auto ident = pop_str();

	auto sym = find_sym_or_err(ident, 
		sconcat("Cannot find symbol called \"", *ident, 
		"\" for len() expression!"));

	//if (sym->type() == SymType::ScalarVarName)
	//{
	//	//push_ir_code(codegen().mk_const(1));
	//}
	//else if (sym->type() == SymType::ArrayVarName)
	//{
	//	//push_ir_code(codegen().mk_const(sym->size()));
	//}
	//else
	//{
	//	err("visitLenExpr():  Eek!\n");
	//}
	push_ir_code(codegen().mk_len(sym));


	return nullptr;
}
antlrcpp::Any Frontend::visitSizeofExpr
	(GrammarParser::SizeofExprContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::expr_sizeof);
//	auto to_push = mk_ast_expr(AstExprOp::Sizeof);
//
//	ctx->identRhs()->accept(this);
//	to_push->append_child(pop_ast_node());
//
//	push_ast_node(to_push);
	err("visitSizeofExpr() is not fully implemented!");
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
