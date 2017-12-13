#include "cstm_grammar_visitor_class.hpp"

CstmGrammarVisitor::~CstmGrammarVisitor()
{
	//printout("~CstmGrammarVisitor()\n");
}

antlrcpp::Any CstmGrammarVisitor::visitProgram
	(GrammarParser::ProgramContext *ctx)
{
	printout("visitProgram()\n");
	////ctx->accept(this);
	const int ret = ctx->statements()->accept(this);

	//for (auto p=ctx->start; p!=ctx->stop; ++p)
	//{
	//	//printout(p->getText(), "\n");
	//	//printout("a");
	//	printout(p->toString(), "\n");
	//}
	//for (auto p : ctx->children)
	//{
	//}
	printout("visitProgram():  ", ret, "\n");

	return ret;
}

antlrcpp::Any CstmGrammarVisitor::visitStatements
	(GrammarParser::StatementsContext *ctx)
{
	printout("visitStatements()\n");
	const int ret = ctx->listStatement()->accept(this);

	return ret;
}

antlrcpp::Any CstmGrammarVisitor::visitListStatement
	(GrammarParser::ListStatementContext *ctx)
{
	printout("visitListStatement()\n");
	//ctx->listStatement()->accept(this);

	
	if (ctx->listStatement())
	{
		// Early statement first
		ctx->listStatement()->accept(this);
	}
	if (ctx->statement())
	{
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
		const int ret = ctx->statements()->accept(this);
		printout("visitStatement():  statements():  ", ret, "\n");
		return ret;
	}
	else if (ctx->expr())
	{
		const int ret = ctx->expr()->accept(this);
		printout("visitStatement():  expr():  ", ret, "\n");
		return ret;
	}
	else
	{
		printerr("visitStatement():  Eek!\n");
		exit(1);
	}

	//if (ctx->assignment())
	//{
	//	ctx->assignment()_
	//}

	return 1;
}

antlrcpp::Any CstmGrammarVisitor::visitAssignment
	(GrammarParser::AssignmentContext *ctx)
{
	return 9000;
}


antlrcpp::Any CstmGrammarVisitor::visitIfStatement
	(GrammarParser::IfStatementContext *ctx)
{
	return 9000;
}
antlrcpp::Any CstmGrammarVisitor::visitIfChainStatement
	(GrammarParser::IfChainStatementContext *ctx)
{
	return 9000;
}
antlrcpp::Any CstmGrammarVisitor::visitElseStatements
	(GrammarParser::ElseStatementsContext *ctx)
{
}
antlrcpp::Any CstmGrammarVisitor::visitWhileStatement
	(GrammarParser::WhileStatementContext *ctx)
{
	return 9000;
}
antlrcpp::Any CstmGrammarVisitor::visitDoWhileStatement
	(GrammarParser::DoWhileStatementContext *ctx)
{
	return 9000;
}


antlrcpp::Any CstmGrammarVisitor::visitExpr
	(GrammarParser::ExprContext *ctx)
{
	if (!ctx->expr())
	{
		//const int expr_ret = ctx->expr()->accept(this);
		//const int expr_logical_ret = ctx->exprLogical()->accept(this);

		const auto& tok_str = ctx->TokOpLogical().getText();

		printout("visitExpr():  tok_str:  ", tok_str, "\n");
	}
	else
	{
		return ctx->exprLogical()->accept(this);
	}
	return 9000;
}

antlrcpp::Any CstmGrammarVisitor::visitExprLogical
	(GrammarParser::ExprLogicalContext *ctx)
{
	return 9000;
}

antlrcpp::Any CstmGrammarVisitor::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
	return 9000;
}

antlrcpp::Any CstmGrammarVisitor::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
	return 9000;
}

antlrcpp::Any CstmGrammarVisitor::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
{
	return 9000;
}

antlrcpp::Any CstmGrammarVisitor::visitIdentExpr
	(GrammarParser::IdentExprContext *ctx)
{
	return 9000;
}
