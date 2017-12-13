#include "cstm_grammar_visitor_class.hpp"
#include "allocation_stuff.hpp"

CstmGrammarVisitor::~CstmGrammarVisitor()
{
	//printout("~CstmGrammarVisitor()\n");
}

antlrcpp::Any CstmGrammarVisitor::visitProgram
	(GrammarParser::ProgramContext *ctx)
{
	printout("visitProgram()\n");
	ctx->statements()->accept(this);
	return 0;
}

antlrcpp::Any CstmGrammarVisitor::visitStatements
	(GrammarParser::StatementsContext *ctx)
{
	printout("visitStatements()\n");
	ctx->listStatement()->accept(this);
	return 0;
}

antlrcpp::Any CstmGrammarVisitor::visitListStatement
	(GrammarParser::ListStatementContext *ctx)
{
	printout("visitListStatement()\n");

	
	if (ctx->listStatement())
	{
		// Early statement first
		printout("visitListStatement():  listStatement()\n");
		ctx->listStatement()->accept(this);
	}
	if (ctx->statement())
	{
		printout("visitListStatement():  statement()\n");
		ctx->statement()->accept(this);
	}

	return 0;

}

antlrcpp::Any CstmGrammarVisitor::visitStatement
	(GrammarParser::StatementContext *ctx)
{
	printout("visitStatement()\n");

	if (ctx->statements())
	{
		printout("visitStatement():  statements()\n");
		ctx->statements()->accept(this);
	}
	else if (ctx->expr())
	{
		ctx->expr()->accept(this);
		printout("visitStatement():  expr():  ", pop_num(), "\n");
	}
	else
	{
		printerr("visitStatement():  Eek!\n");
		exit(1);
	}

	return 0;
}

antlrcpp::Any CstmGrammarVisitor::visitAssignment
	(GrammarParser::AssignmentContext *ctx)
{
	return 0;
}


antlrcpp::Any CstmGrammarVisitor::visitIfStatement
	(GrammarParser::IfStatementContext *ctx)
{
	return 0;
}
antlrcpp::Any CstmGrammarVisitor::visitIfChainStatement
	(GrammarParser::IfChainStatementContext *ctx)
{
	return 0;
}
antlrcpp::Any CstmGrammarVisitor::visitElseStatements
	(GrammarParser::ElseStatementsContext *ctx)
{
	return 0;
}
antlrcpp::Any CstmGrammarVisitor::visitWhileStatement
	(GrammarParser::WhileStatementContext *ctx)
{
	return 0;
}
antlrcpp::Any CstmGrammarVisitor::visitDoWhileStatement
	(GrammarParser::DoWhileStatementContext *ctx)
{
	return 0;
}


antlrcpp::Any CstmGrammarVisitor::visitExpr
	(GrammarParser::ExprContext *ctx)
{
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

	return 0;
}

antlrcpp::Any CstmGrammarVisitor::visitExprLogical
	(GrammarParser::ExprLogicalContext *ctx)
{
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
		return (int)ctx->exprCompare()->accept(this);
	}
}

antlrcpp::Any CstmGrammarVisitor::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
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
	return 0;
}

antlrcpp::Any CstmGrammarVisitor::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
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
	return 0;
}

antlrcpp::Any CstmGrammarVisitor::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
{
	if (ctx->TokDecNum())
	{
		push_num(atoi(ctx->TokDecNum()->toString().c_str()));
	}
	else
	{
		ctx->expr()->accept(this);
	}
	return 0;
}

antlrcpp::Any CstmGrammarVisitor::visitIdentExpr
	(GrammarParser::IdentExprContext *ctx)
{
	return 0;
}
