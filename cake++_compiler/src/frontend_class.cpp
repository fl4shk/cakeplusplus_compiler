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
	auto&& globalFuncDecl = ctx->globalFuncDecl();

	std::vector<GrammarParser::FuncDeclContext*> funcDecl;

	for (auto* global_func_decl : globalFuncDecl)
	{
		global_func_decl->accept(this);
		funcDecl.push_back(pop_func_decl());
	}


	//auto&& funcDecl = ctx->funcDecl();

	for (auto* func_decl : funcDecl)
	{
		func_decl->builtinTypename()->accept(this);
		const auto ret_type = pop_builtin_typename();

		func_decl->identName()->accept(this);
		auto ident = pop_str();

		__func_decl_to_ident_map[func_decl] = ident;

		if (__func_tbl.contains(ident))
		{
			err(ctx, sconcat("Can't have more than one function called \"",
				*ident, "\"!"));
		}

		__func_tbl.insert_or_assign(mk_global_func(ret_type, ident));

		__curr_func = __func_tbl.at(ident);
		__curr_scope_node = curr_func().get_args_scope_node();

		auto&& funcArgDecl = func_decl->funcArgDecl();

		if (funcArgDecl.size() > max_num_func_args)
		{
			err(ctx, sconcat("Function called \"", *ident, "\" takes ",
				"far, far too many arguments!  ",
				"Note:  Max permitted amount is ", max_num_func_args, 
				"."));
		}

		// Fill up the symbol table with the arguments to the function
		for (auto* func_arg_decl : funcArgDecl)
		{
			func_arg_decl->accept(this);
		}
	}

	// Now visit the statements

	{
	Json::Value func_ir_code_json_output_root;

	Json::ArrayIndex index_i = 0;
	
	for (auto* iter : funcDecl)
	{
		auto ident = __func_decl_to_ident_map.at(iter);

		__curr_func = __func_tbl.at(ident);
		__curr_scope_node = curr_func().get_args_scope_node();

		iter->accept(this);

		if constexpr (debug_show_json)
		{
			auto& temp_json_output_root 
				= func_ir_code_json_output_root[index_i];
			codegen().output_func_ir_code_as_json
				(temp_json_output_root, curr_func());

			++index_i;
		}
	}

	if constexpr (debug_show_json)
	{
		write_json(cout, &func_ir_code_json_output_root);
		exit(0);
	}
	}

	{
	bool found_main = false;
	for (auto* iter : funcDecl)
	{
		auto ident = __func_decl_to_ident_map.at(iter);

		if (*ident == "main")
		{
			found_main = true;

			auto temp = __func_tbl.at(ident);

			auto&& temp_args = temp->get_args();

			if (temp_args.size() != 0)
			{
				printerr("Error:  The \"main\" function is not allowed ",
					"to take any arguments!\n");
				exit(1);
			}
		}
		__func_vec.push_back(__func_tbl.at(ident));
	}

	if (!found_main)
	{
		printerr("Error:  No function with identifier \"main\" found!\n");
		exit(1);
	}
	}

	//__vm_backend.reset(new VmBackend(std::move(__func_vec), &__func_tbl));
	//__vm_backend->gen_code();
	//__vm_backend->osprint_code(cout);

	return nullptr;
}
//antlrcpp::Any Frontend::visitClassDecl
//	(GrammarParser::ClassDeclContext *ctx)
//{
//	return nullptr;
//}
antlrcpp::Any Frontend::visitGlobalFuncDecl
	(GrammarParser::GlobalFuncDeclContext *ctx)
{
	push_func_decl(ctx->funcDecl());
	return nullptr;
}
//antlrcpp::Any Frontend::visitMemberFuncDecl
//	(GrammarParser::MemberFuncDeclContext *ctx)
//{
//	push_func_decl(ctx->funcDecl();
//	return nullptr;
//}

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
	ctx->identName()->accept(this);
	auto ident = pop_str();

	Function* func;
	{
	func = __func_tbl.at(ident);
	}

	if (func == nullptr)
	{
		err(ctx, sconcat("Can't find function with identifier \"", *ident, 
			"\"!"));
	}

	//auto to_push = codegen().mk_expr_unfinished_call_with_ret
	//	(convert_builtin_typename_to_mm(func->ret_type()), 
	//	codegen().mk_expr_ref_func(func));
	auto to_push = codegen().mk_pure_expr_unfinished_call_with_ret
		(convert_builtin_typename_to_mm(func->ret_type()), 
		codegen().mk_spec_expr_ref_sym(func->sym()));

	{
	auto&& funcArgExpr = ctx->funcArgExpr();

	auto&& args = func->get_args();
	//auto&& args = func->get_args(sym_tbl());

	if (args.size() != funcArgExpr.size())
	{
		err(ctx, sconcat("Function called \"", *ident, "\" expects ",
			args.size(), " arguments, but instead got ",
			funcArgExpr.size(), " arguments!"));
	}

	for (size_t i=0; i<funcArgExpr.size(); ++i)
	{
		push_func(func);
		push_num(i);
		//push_sym(args.at(i)->var());
		push_sym(args.at(i));

		funcArgExpr.at(i)->accept(this);

		// Append function arguments
		to_push->append_arg(pop_ir_expr());
	}


	}


	push_ir_expr(to_push);
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

	auto sym = find_sym_or_err(ctx, ident,
		sconcat("No symbol exists called \"", *ident, "\"!"));

	// Function argument type checking
	if ((arg_sym->type() == SymType::ScalarVarName)
		&& (sym->type() != SymType::ScalarVarName))
	{
		err(ctx, sconcat("Function called \"", *func->name(),
			"\" expects a scalar value for argument number ",
			which_arg, "!"));
	}
	if (arg_sym->type() == SymType::ArrayVarName)
	{
		if (sym->type() != SymType::ArrayVarName)
		{
			err(ctx, sconcat("Function called \"", *func->name(),
				"\" expects an array value for argument number ",
				which_arg, "!"));
		}
		else if (sym->type() == SymType::ArrayVarName)
		{
			if (arg_sym->var()->type() != sym->var()->type())
			{
				err(ctx, sconcat("Function called \"", *func->name(),
					"\" expects an array of type ",
					arg_sym->var()->type(), " for argument number ",
					which_arg, "!"));
			}
		}
		else
		{
			err(ctx, "visitFuncArgExpr():  Argument type checking Eek!");
		}
	}

	if (sym->type() == SymType::ScalarVarName)
	{
		// Scalars are passed by value

		auto mem = codegen().mk_pure_expr_real_address
			(codegen().mk_spec_expr_ref_sym(sym));
		push_ir_expr(codegen().mk_pure_expr_ld
			(convert_builtin_typename_to_mm(sym->var()->type()), mem));
	}
	else if (sym->type() == SymType::ArrayVarName)
	{
		// Since arrays are passed by reference, we only need to grab the
		// address for this argument

		auto var = sym->var();

		if (var->is_arg())
		{
			push_ir_expr(codegen().mk_pure_expr_real_address
				(codegen().mk_pure_expr_deref
				(codegen().mk_spec_expr_ref_sym(sym))));
		}
		else // if (!var->is_arg())
		{
			push_ir_expr(codegen().mk_pure_expr_real_address
				(codegen().mk_spec_expr_ref_sym(sym)));
		}
	}
	else
	{
		err(ctx, "visitFuncArgExpr():  Eek!\n");
	}

	return nullptr;
}

antlrcpp::Any Frontend::visitStatements
	(GrammarParser::StatementsContext *ctx)
{
	auto&& stmt = ctx->stmt();

	//sym_tbl().mkscope(curr_func().scope_node());
	sym_tbl().mkscope(__curr_scope_node);

	for (auto iter : stmt)
	{
		iter->accept(this);
	}

	//sym_tbl().rmscope(curr_func().scope_node());
	sym_tbl().rmscope(__curr_scope_node);

	return nullptr;
}


antlrcpp::Any Frontend::visitStmt
	(GrammarParser::StmtContext *ctx)
{
	if (ctx->statements())
	{
		ctx->statements()->accept(this);
	}
	else if (ctx->pseudoFuncCallStmt())
	{
		ctx->pseudoFuncCallStmt()->accept(this);
	}
	//else if (ctx->putnStatement())
	//{
	//	ctx->putnStatement()->accept(this);
	//}
	//else if (ctx->varDecl())
	//{
	//	ctx->varDecl()->accept(this);
	//}
	else if (ctx->localVarDecl())
	{
		ctx->localVarDecl()->accept(this);
	}
	else if (ctx->funcCall())
	{
		ctx->funcCall()->accept(this);
		codegen().mk_code_call(pop_ir_expr());
	}
	//else if (ctx->expr())
	//{
	//	ctx->expr()->accept(this);
	//}
	////else if (ctx->exprMulDivModEtc())
	////{
	////	ctx->exprMulDivModEtc()->accept(this);
	////}
	else if (ctx->assignment())
	{
		ctx->assignment()->accept(this);
	}
	else if (ctx->extendedAssignment())
	{
		ctx->extendedAssignment()->accept(this);
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
		err(ctx, "visitStmt():  Eek!");
	}

	return nullptr;
}

antlrcpp::Any Frontend::visitPseudoFuncCallStmt
	(GrammarParser::PseudoFuncCallStmtContext *ctx)
{
	if (ctx->putnStatement())
	{
		ctx->putnStatement()->accept(this);
	}
	else if (ctx->putcharStatement())
	{
		ctx->putcharStatement()->accept(this);
	}
	else
	{
		err(ctx, "visitPseudoFuncCallStmt():  Eek!");
	}

	return nullptr;
}
antlrcpp::Any Frontend::visitPutnStatement
	(GrammarParser::PutnStatementContext *ctx)
{
	ctx->expr()->accept(this);

	auto some_disp_num = codegen().mk_code_unfinished_syscall
		(IrSyscallShorthandOp::DispNum);
	some_disp_num->append_arg(pop_ir_expr());

	//auto some_disp_char = codegen().mk_code_unfinished_syscall
	//	(IrSyscallShorthandOp::DispChar);
	//some_disp_char->append_arg(codegen().mk_pure_expr_constant
	//	(IrMachineMode::U8, '\n'));

	return nullptr;
}

antlrcpp::Any Frontend::visitPutcharStatement
	(GrammarParser::PutcharStatementContext *ctx)
{
	ctx->expr()->accept(this);

	auto some_disp_char = codegen().mk_code_unfinished_syscall
		(IrSyscallShorthandOp::DispChar);
	some_disp_char->append_arg(pop_ir_expr());

	return nullptr;
}

antlrcpp::Any Frontend::visitPseudoFuncCallExpr
	(GrammarParser::PseudoFuncCallExprContext *ctx)
{
	if (ctx->getnExpr())
	{
		ctx->getnExpr()->accept(this);
	}
	else if (ctx->getcharExpr())
	{
		ctx->getcharExpr()->accept(this);
	}
	else
	{
		err(ctx, "visitPseudoFuncCallExpr():  Eek!");
	}
	return nullptr;
}
antlrcpp::Any Frontend::visitGetnExpr
	(GrammarParser::GetnExprContext *ctx)
{
	push_ir_expr(codegen().mk_pure_expr_unfinished_syscall
		(IrMachineMode::S64, IrSyscallShorthandOp::GetNum));
	return nullptr;
}

antlrcpp::Any Frontend::visitGetcharExpr
	(GrammarParser::GetcharExprContext *ctx)
{
	push_ir_expr(codegen().mk_pure_expr_unfinished_syscall
		(IrMachineMode::U8, IrSyscallShorthandOp::GetChar));
	return nullptr;
}

//antlrcpp::Any Frontend::visitMemberVarDecl
//	(GrammarParser::MemberVarDeclContext *ctx)
//{
//	__var_decl_is_func_local = false;
//
//	ctx->varDecl()->accept(this);
//
//	return nullptr;
//}
antlrcpp::Any Frontend::visitLocalVarDecl
	(GrammarParser::LocalVarDeclContext *ctx)
{
	__var_decl_is_func_local = true;

	ctx->varDecl()->accept(this);

	return nullptr;
}
antlrcpp::Any Frontend::visitVarDecl
	(GrammarParser::VarDeclContext *ctx)
{
	if (ctx->builtinTypeVarDecl())
	{
		ctx->builtinTypeVarDecl()->accept(this);
	}
	//else if (ctx->classInstDecl())
	//{
	//	ctx->classInstDecl()->accept(this);
	//}
	else
	{
		err(ctx, "visitVarDecl():  Eek!");
	}
	
	return nullptr;
}

antlrcpp::Any Frontend::visitBuiltinTypeVarDecl
	(GrammarParser::BuiltinTypeVarDeclContext *ctx)
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
	Symbol arg_sym;
	arg_sym.set_var(mk_var());
	ctx->builtinTypename()->accept(this);
	arg_sym.var()->set_type(pop_builtin_typename());
	arg_sym.var()->set_func(__curr_func);

	if (ctx->identName())
	{
		ctx->identName()->accept(this);
		arg_sym.set_type(SymType::ScalarVarName);
	}
	else if (ctx->nonSizedArrayIdentName())
	{
		ctx->nonSizedArrayIdentName()->accept(this);
		arg_sym.set_type(SymType::ArrayVarName);
	}
	else
	{
		err(ctx, "visitFuncArgDecl():  Eek!\n");
	}

	arg_sym.var()->set_name(pop_str());

	{
	//auto existing_sym = sym_tbl().find_in_first_blklev(arg_sym.name());
	//auto existing_sym = sym_tbl().find_func_arg(curr_func().name(),
	//	arg_sym.name());
	//auto existing_sym = sym_tbl().find_func_arg(__curr_scope_node,
	//	arg_sym.name());
	auto existing_sym = sym_tbl().find_func_arg(curr_func().scope_node(),
		arg_sym.name());

	if (existing_sym != nullptr)
	{
		err(ctx, sconcat("Function called \"", *curr_func().name(), 
			"\" cannot have two arguments with same identifiers!\n",
			"Note:  offending argument has identifier \"",
			*arg_sym.name(), "\"."));
	}
	}



	// This is an argument
	arg_sym.var()->set_is_arg(true);

	// Which argument in the list is this? 
	++curr_func().last_arg_offset();
	arg_sym.var()->set_arg_offset(curr_func().last_arg_offset());

	//sym_tbl().insert_or_assign(std::move(arg_sym));
	sym_tbl().insert_or_assign(__curr_scope_node, std::move(arg_sym));

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
		err(ctx, "visitBuiltinTypename():  Eek!\n");
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

	//auto addr = pop_ir_code();
	//auto index = pop_ir_code();

	//ctx->expr()->accept(this);
	//auto expr = pop_ir_code();

	auto sym = pop_sym();

	//push_ir_code(codegen().mk_stx(sym->get_unsgn_or_sgn(),
	//	sym->get_ldst_size(), addr, index, expr));

	auto mem = pop_ir_expr();
	auto index = pop_ir_expr();

	ctx->expr()->accept(this);
	auto expr = pop_ir_expr();

	if (index->is_pure && (index->pure_op == IrPureExOp::Constant) 
		&& (index->simm == 0))
	{
		//codegen().mk_code_st(get_top_mm(), mem, expr);
		codegen().mk_code_st
			(convert_builtin_typename_to_mm(sym->var()->type()), mem, 
				expr);
	}
	else
	{
		//codegen().mk_code_st(get_top_mm(), 
		//	codegen().mk_pure_expr_binop(IrMachineMode::Pointer,
		//	IrBinop::Add, mem, index), expr);

		//codegen().mk_code_st
		//	(convert_builtin_typename_to_mm(sym->var()->type()),
		//	codegen().mk_pure_expr_binop(IrMachineMode::Pointer,
		//	IrBinop::Add, mem, index), expr);

		auto type_size = codegen().mk_pure_expr_constant
			(IrMachineMode::Length, get_builtin_typename_size
			(sym->var()->type()));

		auto multiplied_index = codegen().mk_pure_expr_binop
			(IrMachineMode::Pointer, IrBinop::Mul, type_size, index);

		codegen().mk_code_st
			(convert_builtin_typename_to_mm(sym->var()->type()),
			codegen().mk_pure_expr_binop(IrMachineMode::Pointer,
			IrBinop::Add, mem, multiplied_index), expr);
	}


	return nullptr;
}
antlrcpp::Any Frontend::visitExtendedAssignment
	(GrammarParser::ExtendedAssignmentContext *ctx)
{
	ctx->identLhs()->accept(this);


	auto sym = pop_sym();
	const auto sym_mm = convert_builtin_typename_to_mm(sym->var()->type());


	auto mem = pop_ir_expr();
	auto index = pop_ir_expr();

	ctx->expr()->accept(this);
	auto orig_expr = pop_ir_expr();
	decltype(orig_expr) expr = nullptr;

	auto&& op = ctx->TokOpExtendedAssignment()->toString();

	IrBinop s_binop;


	if (op == "+=")
	{
		s_binop = IrBinop::Add;
	}
	else if (op == "-=")
	{
		s_binop = IrBinop::Sub;
	}
	else if (op == "*=")
	{
		s_binop = IrBinop::Mul;
	}
	else if (op == "/=")
	{
		s_binop = IrBinop::Div;
	}
	else if (op == "%=")
	{
		s_binop = IrBinop::Mod;
	}

	else if (op == "&=")
	{
		s_binop = IrBinop::BitAnd;
	}
	else if (op == "|=")
	{
		s_binop = IrBinop::BitOr;
	}
	else if (op == "^=")
	{
		s_binop = IrBinop::BitXor;
	}
	else if (op == "<<=")
	{
		s_binop = IrBinop::BitShiftLeft;
	}
	else if (op == ">>=")
	{
		s_binop = IrBinop::BitShiftRight;
	}
	else
	{
		err(ctx, "visitExtendedAssignment():  Binop Eek!");
	}

	if (index->is_pure && (index->pure_op == IrPureExOp::Constant) 
		&& (index->simm == 0))
	{
		expr = codegen().mk_pure_expr_binop(sym_mm, s_binop, 
			codegen().mk_pure_expr_ld(sym_mm, mem), orig_expr);
	}
	else
	{
		auto type_size = codegen().mk_pure_expr_constant
			(IrMachineMode::Length, get_builtin_typename_size
			(sym->var()->type()));

		auto multiplied_index = codegen().mk_pure_expr_binop
			(IrMachineMode::Pointer, IrBinop::Mul, type_size, index);

		auto load = codegen().mk_pure_expr_ld(sym_mm,
			codegen().mk_pure_expr_binop(IrMachineMode::Pointer,
			IrBinop::Add, mem, multiplied_index));

		expr = codegen().mk_pure_expr_binop(sym_mm, s_binop, load, 
			orig_expr);
	}


	// Accept again for the store
	ctx->identLhs()->accept(this);
	pop_sym();

	mem = pop_ir_expr();
	index = pop_ir_expr();

	if (index->is_pure && (index->pure_op == IrPureExOp::Constant) 
		&& (index->simm == 0))
	{
		codegen().mk_code_st(sym_mm, mem, expr);
	}
	else
	{
		auto type_size = codegen().mk_pure_expr_constant
			(IrMachineMode::Length, get_builtin_typename_size
			(sym->var()->type()));

		auto multiplied_index = codegen().mk_pure_expr_binop
			(IrMachineMode::Pointer, IrBinop::Mul, type_size, index);

		codegen().mk_code_st(sym_mm,
			codegen().mk_pure_expr_binop(IrMachineMode::Pointer,
			IrBinop::Add, mem, multiplied_index), expr);
	}


	return nullptr;
}
antlrcpp::Any Frontend::visitIfStatement
	(GrammarParser::IfStatementContext *ctx)
{
	//ctx->expr()->accept(this);
	//auto expr = pop_ir_code();


	//auto label_after_statements = codegen().mk_unlinked_label();

	//codegen().mk_branch_if_false(label_after_statements, expr);

	//ctx->statements()->accept(this);

	//relink_ir_code(label_after_statements);



	ctx->expr()->accept(this);
	auto cond = pop_ir_expr();

	auto label_after_statements = codegen().mk_code_unlinked_label();

	//auto ite = codegen().mk_spec_expr_if_then_else(IrMachineMode::Pointer,
	//	cond, codegen().mk_spec_expr_get_next_pc(), 
	//	codegen().mk_pure_expr_address(codegen().mk_spec_expr_ref_lab
	//	(label_after_statements->lab_num())));

	auto ite = codegen().mk_spec_expr_if_then_else(cond,
		codegen().mk_spec_expr_get_next_pc(), 
		label_after_statements->lab_num());

	codegen().mk_code_jump(ite);

	ctx->statements()->accept(this);

	relink_ir_code(label_after_statements);

	return nullptr;
}
antlrcpp::Any Frontend::visitIfChainStatement
	(GrammarParser::IfChainStatementContext *ctx)
{
	//ctx->expr()->accept(this);
	//auto expr = pop_ir_code();

	//auto label_after_statements = codegen().mk_unlinked_label();


	//// Branch to the else stuff if false
	//codegen().mk_branch_if_false(label_after_statements, expr);

	//ctx->statements()->accept(this);



	//auto label_after_else_statements = codegen().mk_unlinked_label();


	//// Branch to the part that's after the elseStatements
	//codegen().mk_bra(label_after_else_statements);

	//relink_ir_code(label_after_statements);

	//ctx->elseStatements()->accept(this);

	//relink_ir_code(label_after_else_statements);



	ctx->expr()->accept(this);
	auto cond = pop_ir_expr();

	auto label_before_else_statements = codegen().mk_code_unlinked_label();


	// Branch to the else stuff if false, or continue if true
	{
	auto ite = codegen().mk_spec_expr_if_then_else(cond,
		codegen().mk_spec_expr_get_next_pc(), 
		label_before_else_statements->lab_num());
	
	codegen().mk_code_jump(ite);
	}

	ctx->statements()->accept(this);

	auto label_after_else_statements = codegen().mk_code_unlinked_label();

	// Unconditionally branch to the part that's after the elseStatements
	codegen().mk_code_jump(codegen().mk_spec_expr_ref_lab
		(label_after_else_statements->lab_num()));

	relink_ir_code(label_before_else_statements);

	ctx->elseStatements()->accept(this);

	relink_ir_code(label_after_else_statements);


	return nullptr;
}
antlrcpp::Any Frontend::visitElseStatements
	(GrammarParser::ElseStatementsContext *ctx)
{
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
	//auto label_before_expr = codegen().mk_label();

	//ctx->expr()->accept(this);
	//auto expr = pop_ir_code();


	//auto label_after_while = codegen().mk_unlinked_label();
	//codegen().mk_branch_if_false(label_after_while, expr);

	//ctx->statements()->accept(this);


	//// For a while loop, always branch back up to the label_before_expr if
	//// we didn't conditionally end the loop.
	//codegen().mk_bra(label_before_expr);

	//relink_ir_code(label_after_while);


	auto label_before_expr = codegen().mk_code_linked_label();

	ctx->expr()->accept(this);
	auto cond = pop_ir_expr();


	auto label_after_while = codegen().mk_code_unlinked_label();

	codegen().mk_code_jump(codegen().mk_spec_expr_if_then_else(cond,
		codegen().mk_spec_expr_get_next_pc(),
		label_after_while->lab_num()));
	
	ctx->statements()->accept(this);

	// For a while loop, always branch back up to the label_before_expr if
	// we didn't conditionally end the loop.
	codegen().mk_code_jump(codegen().mk_spec_expr_ref_lab
		(label_before_expr->lab_num()));
	
	relink_ir_code(label_after_while);


	return nullptr;
}
antlrcpp::Any Frontend::visitDoWhileStatement
	(GrammarParser::DoWhileStatementContext *ctx)
{
	//auto label_before_statements = codegen().mk_label();

	//ctx->statements()->accept(this);


	//ctx->expr()->accept(this);
	//auto expr = pop_ir_code();

	//codegen().mk_bne(label_before_statements, expr);

	auto label_before_statements = codegen().mk_code_linked_label();

	ctx->statements()->accept(this);

	ctx->expr()->accept(this);
	auto cond = pop_ir_expr();

	// Continue the loop if the condition is non-zero
	codegen().mk_code_jump(codegen().mk_spec_expr_if_then_else
		(IrMachineMode::Pointer, cond,
		codegen().mk_pure_expr_real_address(codegen().mk_spec_expr_ref_lab
		(label_before_statements->lab_num())), 
		codegen().mk_spec_expr_get_next_pc()));


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
	//err(ctx, "visitReturnExprStatement() is not fully implemented!");

	ctx->expr()->accept(this);
	codegen().mk_code_return_expr(pop_ir_expr());

	return nullptr;
}
antlrcpp::Any Frontend::visitReturnNothingStatement
	(GrammarParser::ReturnNothingStatementContext *ctx)
{
//	//auto to_push = mk_ast_node(AstOp::stmt_return_nothing);
//	auto to_push = mk_ast_stmt(AstStmtOp::ReturnNothing);
//
//	push_ast_node(to_push);
	err(ctx, "visitReturnNothingStatement() is not fully implemented!");
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
	else // if (ctx->expr())
	{
		////auto to_push = mk_ast_node(AstOp::expr_binop);
		//auto to_push = mk_ast_expr(AstExprOp::Binop);


		ctx->expr()->accept(this);
		//auto a = pop_ir_code();
		////to_push->append_child(pop_ast_node());
		auto a = pop_ir_expr();

		auto&& op = ctx->TokOpLogical()->toString();

		IrBinop s_binop;

		if (op == "&&")
		{
			//to_push->bin_op = AstBinOp::LogAnd;
			//s_binop = IrBinop::BitAnd;
			s_binop = IrBinop::LogAnd;
		}
		else if (op == "||")
		{
			//to_push->bin_op = AstBinOp::LogOr;
			//s_binop = IrBinop::BitOr;
			s_binop = IrBinop::LogOr;
		}
		else
		{
			err(ctx, "visitExpr():  binop type Eek!\n");
		}

		ctx->exprLogical()->accept(this);
		//auto b = pop_ir_code();
		auto b = pop_ir_expr();

		//auto some_binop = codegen().mk_binop(s_binop, a, b);

		//push_ir_expr(codegen().mk_expr_binop(get_top_mm(), s_binop, a, b));
		push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
			s_binop, a, b));
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
	else // if (ctx->exprLogical())
	{
		////auto to_push = mk_ast_node(AstOp::expr_binop);
		//auto to_push = mk_ast_expr(AstExprOp::Binop);


		ctx->exprLogical()->accept(this);
		//auto a = pop_ir_code();
		//to_push->append_child(pop_ast_node());

		auto a = pop_ir_expr();

		auto&& op = ctx->TokOpCompare()->toString();


		IrBinop s_binop;

		if (op == "==")
		{
			s_binop = IrBinop::CmpEq;
		}
		else if (op == "!=")
		{
			s_binop = IrBinop::CmpNe;
		}
		else if (op == "<")
		{
			s_binop = IrBinop::CmpLt;
		}
		else if (op == ">")
		{
			s_binop = IrBinop::CmpGt;
		}
		else if (op == "<=")
		{
			s_binop = IrBinop::CmpLe;
		}
		else if (op == ">=")
		{
			s_binop = IrBinop::CmpGe;
		}
		else
		{
			err(ctx, "visitExprLogical():  binop type Eek!\n");
		}

		ctx->exprCompare()->accept(this);
		auto b = pop_ir_expr();

		push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
			s_binop, a, b));
	}

	return nullptr;
}
//antlrcpp::Any Frontend::visitExprCompare
//	(GrammarParser::ExprCompareContext *ctx)
//{
//	//if (ctx->exprAddSub())
//	if (!ctx->exprCompare())
//	{
//		ctx->exprAddSub()->accept(this);
//	}
//	else // if (ctx->exprCompare())
//	{
//		////auto to_push = mk_ast_node(AstOp::expr_binop);
//		//auto to_push = mk_ast_expr(AstExprOp::Binop);
//
//
//		ctx->exprCompare()->accept(this);
//		auto a = pop_ir_expr();
//
//		//to_push->append_child(pop_ast_node());
//
//		auto&& op = ctx->TokOpAddSub()->toString();
//
//		IrBinop s_binop;
//
//		if (op == "+")
//		{
//			s_binop = IrBinop::Add;
//		}
//		else if (op == "-")
//		{
//			s_binop = IrBinop::Sub;
//		}
//		else
//		{
//			err(ctx, "visitExprCompare():  binop type Eek!\n");
//		}
//
//		ctx->exprAddSub()->accept(this);
//		auto b = pop_ir_expr();
//
//		//push_ir_expr(codegen().mk_expr_binop(get_top_mm(), s_binop, a, b));
//		push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
//			s_binop, a, b));
//	}
//
//	return nullptr;
//}

antlrcpp::Any Frontend::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
	if (ctx->exprAddSub())
	{
		ctx->exprAddSub()->accept(this);
	}
	else if (ctx->exprJustAdd())
	{
		ctx->exprJustAdd()->accept(this);
	}
	else if (ctx->exprJustSub())
	{
		ctx->exprJustSub()->accept(this);
	}
	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustAdd
	(GrammarParser::ExprJustAddContext *ctx)
{
	ctx->exprAddSub()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprCompare()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::Add, a, b));

	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustSub
	(GrammarParser::ExprJustSubContext *ctx)
{
	ctx->exprAddSub()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprCompare()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::Sub, a, b));

	return nullptr;
}
antlrcpp::Any Frontend::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
	////if (ctx->exprMulDivModEtc())
	//if (!ctx->exprAddSub())
	//{
	//	ctx->exprMulDivModEtc()->accept(this);
	//}
	//else // if (ctx->exprAddSub())
	//{
	//	////auto to_push = mk_ast_node(AstOp::expr_binop);
	//	//auto to_push = mk_ast_expr(AstExprOp::Binop);


	//	ctx->exprAddSub()->accept(this);
	//	auto a = pop_ir_expr();

	//	//to_push->append_child(pop_ast_node());

	//	std::string op;
	//	
	//	if (ctx->TokOpMulDivMod())
	//	{
	//		op = ctx->TokOpMulDivMod()->toString();
	//	}
	//	else if (ctx->TokOpBitwise())
	//	{
	//		op = ctx->TokOpBitwise()->toString();
	//	}
	//	else
	//	{
	//		err(ctx, "visitExprAddSub():  operator Eek!\n");
	//	}

	//	IrBinop s_binop;

	//	if (op == "*")
	//	{
	//		s_binop = IrBinop::Mul;
	//	}
	//	else if (op == "/")
	//	{
	//		s_binop = IrBinop::Div;
	//	}
	//	else if (op == "%")
	//	{
	//		s_binop = IrBinop::Mod;
	//	}
	//	else if (op == "&")
	//	{
	//		s_binop = IrBinop::BitAnd;
	//	}
	//	else if (op == "|")
	//	{
	//		s_binop = IrBinop::BitOr;
	//	}
	//	else if (op == "^")
	//	{
	//		s_binop = IrBinop::BitXor;
	//	}
	//	else if (op == "<<")
	//	{
	//		s_binop = IrBinop::BitShiftLeft;
	//	}
	//	else if (op == ">>")
	//	{
	//		s_binop = IrBinop::BitShiftRight;
	//	}
	//	//else if (op == ">>>")
	//	//{
	//	//	//to_push->bin_op = AstBinOp::BitAsr;
	//	//	s_binop = IrBinop::BitAsr;
	//	//}
	//	else
	//	{
	//		err(ctx, "visitExprAddSub():  binop type Eek!\n");
	//	}

	//	ctx->exprMulDivModEtc()->accept(this);
	//	auto b = pop_ir_expr();

	//	//push_ir_expr(codegen().mk_expr_binop(get_top_mm(), s_binop, a, b));
	//	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
	//		s_binop, a, b));
	//}

	if (ctx->exprJustMul())
	{
		ctx->exprJustMul()->accept(this);
	}
	else if (ctx->exprJustDiv())
	{
		ctx->exprJustDiv()->accept(this);
	}
	else if (ctx->exprJustMod())
	{
		ctx->exprJustMod()->accept(this);
	}
	else if (ctx->exprJustBitAnd())
	{
		ctx->exprJustBitAnd()->accept(this);
	}
	else if (ctx->exprJustBitOr())
	{
		ctx->exprJustBitOr()->accept(this);
	}
	else if (ctx->exprJustBitXor())
	{
		ctx->exprJustBitXor()->accept(this);
	}
	else if (ctx->exprJustBitShiftLeft())
	{
		ctx->exprJustBitShiftLeft()->accept(this);
	}
	else if (ctx->exprJustBitShiftRight())
	{
		ctx->exprJustBitShiftRight()->accept(this);
	}
	else if (ctx->exprMulDivModEtc())
	{
		ctx->exprMulDivModEtc()->accept(this);
	}
	else
	{
		err(ctx, "visitExprAddSub():  Eek!");
	}

	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustMul
	(GrammarParser::ExprJustMulContext *ctx)
{
	ctx->exprMulDivModEtc()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprAddSub()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::Mul, a, b));

	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustDiv
	(GrammarParser::ExprJustDivContext *ctx)
{
	ctx->exprMulDivModEtc()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprAddSub()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::Div, a, b));

	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustMod
	(GrammarParser::ExprJustModContext *ctx)
{
	ctx->exprMulDivModEtc()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprAddSub()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::Mod, a, b));

	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustBitAnd
	(GrammarParser::ExprJustBitAndContext *ctx)
{
	ctx->exprMulDivModEtc()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprAddSub()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::BitAnd, a, b));

	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustBitOr
	(GrammarParser::ExprJustBitOrContext *ctx)
{
	ctx->exprMulDivModEtc()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprAddSub()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::BitOr, a, b));

	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustBitXor
	(GrammarParser::ExprJustBitXorContext *ctx)
{
	ctx->exprMulDivModEtc()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprAddSub()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::BitXor, a, b));

	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustBitShiftLeft
	(GrammarParser::ExprJustBitShiftLeftContext *ctx)
{
	ctx->exprMulDivModEtc()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprAddSub()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::BitShiftLeft, a, b));

	return nullptr;
}
antlrcpp::Any Frontend::visitExprJustBitShiftRight
	(GrammarParser::ExprJustBitShiftRightContext *ctx)
{
	ctx->exprMulDivModEtc()->accept(this);
	auto a = pop_ir_expr();

	ctx->exprAddSub()->accept(this);
	auto b = pop_ir_expr();

	push_ir_expr(codegen().mk_pure_expr_binop(get_mm_for_binop(a, b),
		IrBinop::BitShiftRight, a, b));

	return nullptr;
}


antlrcpp::Any Frontend::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
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
	//if (ctx->exprUnary())
	//{
	//	ctx->exprUnary()->accept(this);
	//}
	else if (ctx->numExpr())
	{
		ctx->numExpr()->accept(this);

		//push_ir_code(codegen().mk_const(pop_num()));
		//push_ir_expr(codegen().mk_expr_constant(get_top_mm(), pop_num()));
		push_ir_expr(codegen().mk_pure_expr_constant(IrMachineMode::S64,
			pop_num()));
	}
	else if (ctx->funcCall())
	{
		ctx->funcCall()->accept(this);
	}
	else if (ctx->pseudoFuncCallExpr())
	{
		ctx->pseudoFuncCallExpr()->accept(this);
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
	else if (ctx->castExpr())
	{
		ctx->castExpr()->accept(this);
	}
	else if (ctx->expr())
	{
		ctx->expr()->accept(this);
	}
	else
	{
		err(ctx, "visitExprMulDivModEtc():  Eek!\n");
	}
	return nullptr;
}

//antlrcpp::Any Frontend::visitExprUnary
//	(GrammarParser::ExprUnaryContext *ctx)
//{
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
//		err(ctx, "visitExprUnary():  Eek!\n");
//	}
//	return nullptr;
//}
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

	//push_ir_expr(codegen().mk_expr_unop(get_top_mm(), IrUnop::BitNot,
	//	pop_ir_expr()));

	auto expr = pop_ir_expr();
	push_ir_expr(codegen().mk_pure_expr_unop(expr->mm, IrUnop::BitNot, 
		expr));

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

	//push_ir_expr(codegen().mk_expr_unop(get_top_mm(), IrUnop::Negate,
	//	pop_ir_expr()));

	auto expr = pop_ir_expr();
	push_ir_expr(codegen().mk_pure_expr_unop(expr->mm, IrUnop::Negate, 
		expr));

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

	//push_ir_expr(codegen().mk_expr_unop(get_top_mm(), IrUnop::LogNot,
	//	pop_ir_expr()));

	auto expr = pop_ir_expr();
	push_ir_expr(codegen().mk_pure_expr_unop(expr->mm, IrUnop::LogNot, 
		expr));

	return nullptr;
}

void Frontend::__visit_ident_access
	(GrammarParser::IdentNameContext* ctx_ident_name,
	GrammarParser::SubscriptExprContext* ctx_subscript_expr)
{
	ctx_ident_name->accept(this);
	auto ident = pop_str();

	auto sym = find_sym_or_err(ctx_ident_name, ident, 
		sconcat("No symbol with identifier \"", *ident, 
		"\" was found!"));

	//auto addr = codegen().mk_address(sym);
	//auto mem = codegen().mk_pure_expr_address
	//	(codegen().mk_spec_expr_ref_sym(sym));

	//auto mem = codegen().mk_pure_expr_arr_data_address
	//	(codegen().mk_spec_expr_ref_sym(sym));
	IrExpr * mem, * index;

	
	if (sym->type() == SymType::ScalarVarName)
	{
		if (!ctx_subscript_expr)
		{
			mem = codegen().mk_pure_expr_real_address
				(codegen().mk_spec_expr_ref_sym(sym));
			//index = codegen().mk_const(0);
			index = codegen().mk_pure_expr_constant
				(IrMachineMode::Pointer, 0);
		}
		else // if (ctx_subscript_expr)
		{
			err(ctx_ident_name, sconcat("Symbol with identifier \"", 
				*ident, "\" is not an array!"));
		}
	}

	else if (sym->type() == SymType::ArrayVarName)
	{
		if (!ctx_subscript_expr)
		{
			err(ctx_ident_name, sconcat("Symbol with identifier \"", 
				*ident, "\" is an array!"));
		}
		else // if (ctx_subscript_expr)
		{
			auto var = sym->var();

			if (var->is_arg())
			{
				mem = codegen().mk_pure_expr_arr_data_address
					(codegen().mk_pure_expr_deref
					(codegen().mk_spec_expr_ref_sym(sym)));
			}
			else // if (!var->is_arg())
			{
				mem = codegen().mk_pure_expr_arr_data_address
					(codegen().mk_spec_expr_ref_sym(sym));
			}
			ctx_subscript_expr->accept(this);
			//index = pop_ir_code();
			index = pop_ir_expr();
		}
	}
	else
	{
		err(ctx_ident_name, "__visit_ident_access():  Unknown SymType!");
	}

	//push_ir_code(codegen().mk_ldx(addr, index));
	push_sym(sym);
	//push_ir_code(index);
	//push_ir_code(addr);
	push_ir_expr(index);
	push_ir_expr(mem);
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

	//auto addr = pop_ir_code();
	//auto index = pop_ir_code();
	auto mem = pop_ir_expr();
	auto index = pop_ir_expr();


	auto sym = pop_sym();


	//push_ir_code(codegen().mk_ldx(sym->get_unsgn_or_sgn(), 
	//	sym->get_ldst_size(), addr, index));


	// Subscript zero or non-array access
	if (index->is_pure && (index->pure_op == IrPureExOp::Constant) 
		&& (index->simm == 0))
	{
		//push_ir_expr(codegen().mk_expr_ld(get_top_mm(), mem));
		push_ir_expr(codegen().mk_pure_expr_ld
			(convert_builtin_typename_to_mm(sym->var()->type()), mem));
	}
	else
	{
		//push_ir_expr(codegen().mk_expr_ld(get_top_mm(),
		//	codegen().mk_expr_binop(IrMachineMode::Pointer,
		//	IrBinop::Add, mem, index)));

		//push_ir_expr(codegen().mk_pure_expr_ld
		//	(convert_builtin_typename_to_mm(sym->var()->type()),
		//	codegen().mk_pure_expr_binop(IrMachineMode::Pointer,
		//	IrBinop::Add, mem, index)));

		auto type_size = codegen().mk_pure_expr_constant
			(IrMachineMode::Length, 
			get_builtin_typename_size(sym->var()->type()));

		auto multiplied_index = codegen().mk_pure_expr_binop
			(IrMachineMode::Pointer, IrBinop::Mul, type_size, index);

		push_ir_expr(codegen().mk_pure_expr_ld
			(convert_builtin_typename_to_mm(sym->var()->type()),
			codegen().mk_pure_expr_binop(IrMachineMode::Pointer,
			IrBinop::Add, mem, multiplied_index)));

	}

	return nullptr;
}
antlrcpp::Any Frontend::visitIdentDecl
	(GrammarParser::IdentDeclContext *ctx)
{
	//Symbol var;
	Symbol sym;
	sym.set_var(mk_var());
	sym.var()->set_type(pop_builtin_typename());
	sym.var()->set_func(__curr_func);

	ctx->identName()->accept(this);
	sym.var()->set_name(pop_str());

	if (sym_tbl().find_in_this_blklev(__curr_scope_node, sym.var()->name()) 
		!= nullptr)
	{
		err(ctx, sconcat("Symbol with identifier \"", *sym.var()->name(), 
			"\" already exists in this scope!\n"));
	}

	if (!ctx->subscriptConst())
	{
		sym.set_type(SymType::ScalarVarName);
		sym.var()->set_dim(1);
	}
	else // if (ctx->subscriptConst())
	{
		sym.set_type(SymType::ArrayVarName);
		ctx->subscriptConst()->accept(this);
		sym.var()->set_dim(pop_num());
	}

	sym.var()->set_non_size_used_space(calc_var_non_size_used_space
		(get_builtin_typename_size(sym.var()->type()), sym.var()->dim()));

	// This is not an argument.
	sym.var()->set_is_arg(false);

	// Which local variable is this? 
	++curr_func().last_local_var_offset();
	sym.var()->set_local_var_offset(curr_func().last_local_var_offset());
	sym_tbl().insert_or_assign(__curr_scope_node, std::move(sym));


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
	//err(ctx, "visitLenExpr() is not fully implemented!");

	ctx->identName()->accept(this);

	auto ident = pop_str();

	auto sym = find_sym_or_err(ctx, ident, 
		sconcat("Cannot find symbol called \"", *ident, 
		"\" for len() expression!"));

	//push_ir_expr(codegen().mk_expr_len(get_top_mm(),
	//	codegen().mk_expr_ref_sym(sym)));
	push_ir_expr(codegen().mk_pure_expr_len(IrMachineMode::Length,
		codegen().mk_spec_expr_ref_sym(sym)));


	return nullptr;
}
antlrcpp::Any Frontend::visitSizeofExpr
	(GrammarParser::SizeofExprContext *ctx)
{
	//err(ctx, "visitSizeofExpr() is not fully implemented!");
	//return nullptr;

	ctx->identName()->accept(this);

	auto ident = pop_str();

	auto sym = find_sym_or_err(ctx, ident, 
		sconcat("Cannot find symbol called \"", *ident, 
		"\" for sizeof() expression!"));


	//push_ir_code(codegen().mk_len(sym));
	//push_ir_expr(codegen().mk_expr_sizeof(get_top_mm(),
	//	codegen().mk_expr_ref_sym(sym)));
	push_ir_expr(codegen().mk_pure_expr_sizeof(IrMachineMode::Length,
		codegen().mk_spec_expr_ref_sym(sym)));

	return nullptr;
}

antlrcpp::Any Frontend::visitCastExpr
	(GrammarParser::CastExprContext *ctx)
{
	ctx->builtinTypename()->accept(this);

	ctx->expr()->accept(this);

	//auto expr = pop_ir_expr();
	//expr->mm = convert_builtin_typename_to_mm(pop_builtin_typename());
	//push_ir_expr(expr);

	push_ir_expr(codegen().mk_pure_expr_cast
		(convert_builtin_typename_to_mm(pop_builtin_typename()),
		pop_ir_expr()));

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
