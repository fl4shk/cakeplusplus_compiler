#include "interpreter_class.hpp"

#include "allocation_stuff.hpp"

Interpreter::~Interpreter()
{
	//printout("~Interpreter()\n");
}

antlrcpp::Any Interpreter::visitProgram
	(GrammarParser::ProgramContext *ctx)
{
	//printout("visitProgram()\n");
	ctx->statements()->accept(this);
	return nullptr;
}

antlrcpp::Any Interpreter::visitStatements
	(GrammarParser::StatementsContext *ctx)
{
	//printout("visitStatements()\n");
	__sym_tbl.mkscope();
	ctx->listStatement()->accept(this);
	__sym_tbl.rmscope();
	return nullptr;
}

antlrcpp::Any Interpreter::visitListStatement
	(GrammarParser::ListStatementContext *ctx)
{
	//printout("visitListStatement()\n");

	
	if (ctx->listStatement())
	{
		// Early statement first
		//printout("visitListStatement():  listStatement()\n");
		ctx->listStatement()->accept(this);
	}
	if (ctx->statement())
	{
		//printout("visitListStatement():  statement()\n");
		ctx->statement()->accept(this);
	}

	return nullptr;

}

antlrcpp::Any Interpreter::visitStatement
	(GrammarParser::StatementContext *ctx)
{
	//printout("visitStatement()\n");

	if (ctx->statements())
	{
		//printout("visitStatement():  statements()\n");
		ctx->statements()->accept(this);
	}
	else if (ctx->varDecl())
	{
		ctx->varDecl()->accept(this);
	}
	else if (ctx->putNStatement())
	{
		ctx->putNStatement()->accept(this);
	}
	else if (ctx->expr())
	{
		//printout("visitStatement():  expr()\n");
		ctx->expr()->accept(this);
		const int temp = pop_num();
		//printout("visitStatement():  expr():  ", temp, "\n");
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
	else
	{
		printerr("visitStatement():  Eek!\n");
		exit(1);
	}

	return nullptr;
}

antlrcpp::Any Interpreter::visitVarDecl
	(GrammarParser::VarDeclContext *ctx)
{
	ctx->identDecl()->accept(this);
	auto some_ident = pop_str();
	const int subscript = pop_num();

	if (__sym_tbl.find(*some_ident) != nullptr)
	{
		printerr("A variable called \"", *some_ident,
			"\" already exists in this scope!\n");
		exit(1);
	}
	Symbol to_insert(*some_ident, SymType::VarName);
	to_insert.set_var_type(BuiltinTypename::Int);

	if (subscript <= 0)
	{
		printerr("An array size of less than or equal to zero is an ",
			"error!\n");
		exit(1);
	}

	for (int i=0; i<subscript; ++i)
	{
		to_insert.data().push_back(0);
	}
	__sym_tbl.insert_or_assign(std::move(to_insert));

	return nullptr;
}
antlrcpp::Any Interpreter::visitPutNStatement
	(GrammarParser::PutNStatementContext *ctx)
{
	ctx->expr()->accept(this);
	printout(pop_num(), "\n");
}
antlrcpp::Any Interpreter::visitAssignment
	(GrammarParser::AssignmentContext *ctx)
{
	//printout("visitAssignment()\n");
	ctx->identExpr()->accept(this);
	auto some_ident = pop_str();
	const unsigned int subscript = pop_num();

	auto sym = __sym_tbl.find(*some_ident);

	if (sym == nullptr)
	{
		printerr("No identifier called \"", *some_ident,
			"\" exists in this scope!\n");
		exit(1);
	}

	if (subscript >= sym->data().size())
	{
		printerr("Subscript of ", subscript, 
			" is out of range for array called \"", *some_ident, 
			"\"!  Note:  array has size of ", sym->data().size(), 
			".\n");
		exit(1);
	}

	ctx->expr()->accept(this);
	sym->data().at(subscript) = pop_num();

	return nullptr;
}


antlrcpp::Any Interpreter::visitIfStatement
	(GrammarParser::IfStatementContext *ctx)
{
	//printout("visitIfStatement()\n");
	return nullptr;
}
antlrcpp::Any Interpreter::visitIfChainStatement
	(GrammarParser::IfChainStatementContext *ctx)
{
	//printout("visitIfChainStatement()\n");
	return nullptr;
}
antlrcpp::Any Interpreter::visitElseStatements
	(GrammarParser::ElseStatementsContext *ctx)
{
	//printout("visitElseStatements()\n");
	return nullptr;
}
antlrcpp::Any Interpreter::visitWhileStatement
	(GrammarParser::WhileStatementContext *ctx)
{
	//printout("visitWhileStatement()\n");
	return nullptr;
}
antlrcpp::Any Interpreter::visitDoWhileStatement
	(GrammarParser::DoWhileStatementContext *ctx)
{
	//printout("visitDoWhileStatement()\n");
	return nullptr;
}


antlrcpp::Any Interpreter::visitExpr
	(GrammarParser::ExprContext *ctx)
{
	//printout("visitExpr()\n");
	if (ctx->expr())
	{
		ctx->expr()->accept(this);
		const int left = pop_num();
		ctx->exprLogical()->accept(this);
		const int right = pop_num();

		const auto tok_str = std::move(ctx->TokOpLogical()->toString());

		if (tok_str == "&&")
		{
			push_num(left && right);
		}
		else if (tok_str == "||")
		{
			push_num(left || right);
		}
		else
		{
			printerr("visitExpr():  Eek!\n");
			exit(1);
		}
	}
	else
	{
		ctx->exprLogical()->accept(this);
	}

	return nullptr;
}

antlrcpp::Any Interpreter::visitExprLogical
	(GrammarParser::ExprLogicalContext *ctx)
{
	//printout("visitExprLogical()\n");
	if (ctx->exprLogical())
	{
		ctx->exprLogical()->accept(this);
		const int left = pop_num();
		ctx->exprCompare()->accept(this);
		const int right = pop_num();

		const auto tok_str = std::move(ctx->TokOpCompare()->toString());

		if (tok_str == "==")
		{
			push_num(left == right);
		}
		else if (tok_str == "!=")
		{
			push_num(left != right);
		}
		else if (tok_str == "<")
		{
			push_num(left < right);
		}
		else if (tok_str == ">")
		{
			push_num(left > right);
		}
		else if (tok_str == "<=")
		{
			push_num(left <= right);
		}
		else if (tok_str == ">=")
		{
			push_num(left >= right);
		}
		else
		{
			printerr("visitExprLogical():  Eek!\n");
			exit(1);
		}
	}
	else
	{
		return ctx->exprCompare()->accept(this);
	}
}

antlrcpp::Any Interpreter::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
	//printout("visitExprCompare()\n");
	if (ctx->exprCompare())
	{
		ctx->exprCompare()->accept(this);
		const int left = pop_num();
		ctx->exprAddSub()->accept(this);
		const int right = pop_num();

		const auto tok_str = std::move(ctx->TokOpAddSub()->toString());

		if (tok_str == "+")
		{
			push_num(left + right);
		}
		else if (tok_str == "-")
		{
			push_num(left - right);
		}
		else
		{
			printerr("visitExprCompare():  Eek!\n");
			exit(1);
		}
	}
	else
	{
		ctx->exprAddSub()->accept(this);
	}
	return nullptr;
}

antlrcpp::Any Interpreter::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
	//printout("visitExprAddSub()\n");
	if (ctx->exprAddSub())
	{
		ctx->exprAddSub()->accept(this);
		const int left = pop_num();
		ctx->exprMulDivModEtc()->accept(this);
		const int right = pop_num();

		std::string tok_str;

		if (ctx->TokOpMulDivMod())
		{
			tok_str = std::move(ctx->TokOpMulDivMod()->toString());
		}
		else
		{
			tok_str = std::move(ctx->TokOpBitwise()->toString());
		}

		if (tok_str == "*")
		{
			push_num(left * right);
		}
		else if (tok_str == "/")
		{
			push_num(left / right);
		}
		else if (tok_str == "%")
		{
			push_num(left % right);
		}
		else if (tok_str == "&")
		{
			push_num(left & right);
		}
		else if (tok_str == "|")
		{
			push_num(left | right);
		}
		else if (tok_str == "^")
		{
			push_num(left ^ right);
		}
		else if (tok_str == "<<")
		{
			push_num(left << right);
		}
		else if (tok_str == ">>")
		{
			const unsigned int left_u = left;
			const unsigned int right_u = right;
			const unsigned int to_push = left_u >> right_u;
			push_num(to_push);
		}
		else if (tok_str == ">>>")
		{
			push_num(left >> right);
		}
		else
		{
			printerr("visitExprAddSub():  Eek!\n");
			exit(1);
		}
	}
	else
	{
		ctx->exprMulDivModEtc()->accept(this);
	}
	return nullptr;
}

antlrcpp::Any Interpreter::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
{
	//printout("visitExprMulDivModEtc()\n");
	if (ctx->identExpr())
	{
		ctx->identExpr()->accept(this);
		auto some_ident = pop_str();
		const unsigned int subscript = pop_num();

		auto sym = __sym_tbl.find(*some_ident);

		if (sym == nullptr)
		{
			printerr("No identifier called \"", *some_ident,
				"\" exists in this scope!\n");
			exit(1);
		}

		if (subscript >= sym->data().size())
		{
			printerr("Subscript of ", subscript, 
				" is out of range for array called \"", *some_ident, 
				"\"!  Note:  array has size of ", sym->data().size(), 
				".\n");
		}

		push_num(sym->data().at(subscript));
	}
	//else if (ctx->TokDecNum())
	//{
	//	//printout("TokDecNum()\n");
	//	push_num(atoi(ctx->TokDecNum()->toString().c_str()));
	//}
	else if (ctx->numExpr())
	{
		ctx->numExpr()->accept(this);
	}
	else
	{
		ctx->expr()->accept(this);
	}
	return nullptr;
}

antlrcpp::Any Interpreter::visitIdentExpr
	(GrammarParser::IdentExprContext *ctx)
{
	ctx->identName()->accept(this);

	if (ctx->subscriptExpr())
	{
		ctx->subscriptExpr()->accept(this);
	}
	else
	{
		push_num(0);
	}


	return nullptr;
}

antlrcpp::Any Interpreter::visitIdentDecl
	(GrammarParser::IdentDeclContext *ctx)
{
	ctx->identName()->accept(this);

	if (ctx->subscriptConst())
	{
		ctx->subscriptConst()->accept(this);
	}
	else
	{
		push_num(1);
	}

	return nullptr;
}
antlrcpp::Any Interpreter::visitIdentName
	(GrammarParser::IdentNameContext *ctx)
{
	push_str(cstm_strdup(ctx->TokIdent()->toString()));
	return nullptr;
}

antlrcpp::Any Interpreter::visitNumExpr
	(GrammarParser::NumExprContext* ctx)
{
	push_num(atoi(ctx->TokDecNum()->toString().c_str()));
	return nullptr;
}
antlrcpp::Any Interpreter::visitSubscriptExpr
	(GrammarParser::SubscriptExprContext* ctx)
{
	ctx->expr()->accept(this);
	return nullptr;
}


antlrcpp::Any Interpreter::visitSubscriptConst
	(GrammarParser::SubscriptConstContext* ctx)
{
	ctx->numExpr()->accept(this);
	return nullptr;
}
