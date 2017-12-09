#include "abstract_syntax_tree_class.hpp"

AbstractSyntaxTree ast;


AbstractSyntaxTree::AbstractSyntaxTree()
{
}

AbstractSyntaxTree::~AbstractSyntaxTree()
{
}


AstNode* AbstractSyntaxTree::gen_program(AstNode* some_statements)
{
	AstNode* p = mknode<AstProgram>();

	p->append_child(some_statements);

	if (__program != nullptr)
	{
		printerr("AbstractSyntaxTree::gen_program():  Eek!\n");
		exit(1);
	}
	__program = p;

	return p;
}
AstNode* AbstractSyntaxTree::gen_statements(AstNode* some_mkscope, 
	AstNode* some_list_statements, AstNode* some_rmscope)
{
	AstNode* p = mknode<AstStatements>();
	p->append_child(some_mkscope);
	p->append_child(some_list_statements);
	p->append_child(some_rmscope);

	return p;
}
AstNode* AbstractSyntaxTree::gen_list_statement()
{
	AstNode* p = mknode<AstListStatement>();

	return p;
}
AstNode* AbstractSyntaxTree::gen_statement()
{
	AstNode* p = mknode<AstStatement>();

	return p;
}
AstNode* AbstractSyntaxTree::gen_constant(int some_num)
{
	AstNode* p = mknode<AstConstant>();
	p->num = some_num;

	return p;
}
AstNode* AbstractSyntaxTree::gen_ident(const char* some_ident)
{
	AstNode* p = mknode<AstIdent>();
	//printout("AbstractSyntaxTree::gen_ident():  ", some_ident, "\n");

	p->text.push_back(std::string(some_ident));

	return p;
}
AstNode* AbstractSyntaxTree::gen_mkscope()
{
	AstNode* p = mknode<AstMkScope>();

	return p;
}
AstNode* AbstractSyntaxTree::gen_rmscope()
{
	AstNode* p = mknode<AstRmScope>();

	return p;
}
AstNode* AbstractSyntaxTree::gen_assign(const char* some_ident, 
	AstNode* some_expr)
{
	AstNode* ident_node = gen_ident(some_ident);

	AstNode* p = mknode<AstAssign>();
	p->append_child(ident_node);
	p->append_child(some_expr);

	return p;
}
AstNode* AbstractSyntaxTree::gen_binop(const char* some_op, AstNode* a, 
	AstNode* b)
{
	AstNode* p = mknode<AstBinop>();
	p->text.push_back(some_op);
	p->append_child(a);
	p->append_child(b);

	//printout("AbstractSyntaxTree::gen_binop():  some_op ==  ", some_op,
	//	"\n");

	if (some_op == std::string("+"))
	{
		p->binop = AstNodeBinop::Plus;
	}
	else if (some_op == std::string("-"))
	{
		p->binop = AstNodeBinop::Minus;
	}
	else if (some_op == std::string("*"))
	{
		p->binop = AstNodeBinop::Multiplies;
	}
	else if (some_op == std::string("/"))
	{
		p->binop = AstNodeBinop::Divides;
	}
	else if (some_op == std::string("%"))
	{
		p->binop = AstNodeBinop::Modulo;
	}
	else if (some_op == std::string("=="))
	{
		p->binop = AstNodeBinop::CmpEq;
	}
	else if (some_op == std::string("!="))
	{
		p->binop = AstNodeBinop::CmpNe;
	}
	else if (some_op == std::string("<"))
	{
		p->binop = AstNodeBinop::CmpLt;
	}
	else if (some_op == std::string(">"))
	{
		p->binop = AstNodeBinop::CmpGt;
	}
	else if (some_op == std::string("<="))
	{
		p->binop = AstNodeBinop::CmpLe;
	}
	else if (some_op == std::string(">="))
	{
		p->binop = AstNodeBinop::CmpGe;
	}
	else if (some_op == std::string("&&"))
	{
		p->binop = AstNodeBinop::LogicAnd;
	}
	else if (some_op == std::string("||"))
	{
		p->binop = AstNodeBinop::LogicOr;
	}
	else if (some_op == std::string("&"))
	{
		p->binop = AstNodeBinop::BitAnd;
	}
	else if (some_op == std::string("|"))
	{
		p->binop = AstNodeBinop::BitOr;
	}
	else if (some_op == std::string("^"))
	{
		p->binop = AstNodeBinop::BitXor;
	}
	else if (some_op == std::string("<<"))
	{
		p->binop = AstNodeBinop::BitLsl;
	}
	else if (some_op == std::string(">>"))
	{
		p->binop = AstNodeBinop::BitLsr;
	}
	else if (some_op == std::string(">>>"))
	{
		p->binop = AstNodeBinop::BitAsr;
	}
	else
	{
		printerr("AbstractSyntaxTree::gen_binop():  Eek!\n");
		exit(1);
	}

	return p;
}

AstNode* AbstractSyntaxTree::gen_if_statement(AstNode* some_expr, 
	AstNode* some_statement)
{
	AstNode* p = mknode<AstIf>();

	p->append_child(some_expr);
	p->append_child(some_statement);

	return p;
}
AstNode* AbstractSyntaxTree::gen_if_chain_statement(AstNode* some_expr,
	AstNode* some_statement_if, AstNode* some_statement_else)
{
	AstNode* p = mknode<AstIfChain>();

	p->append_child(some_expr);
	p->append_child(some_statement_if);
	p->append_child(some_statement_else);

	return p;
}
AstNode* AbstractSyntaxTree::gen_while_statement(AstNode* some_expr,
	AstNode* some_statement)
{
	AstNode* p = mknode<AstWhile>();

	p->append_child(some_expr);
	p->append_child(some_statement);

	return p;
}
AstNode* AbstractSyntaxTree::gen_do_while_statement
	(AstNode* some_statement, AstNode* some_expr)
{
	AstNode* p = mknode<AstDoWhile>();

	p->append_child(some_statement);
	p->append_child(some_expr);

	return p;
}


