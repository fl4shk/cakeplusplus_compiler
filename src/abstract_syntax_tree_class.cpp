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
	AstNode* p = mknode();
	p->op = AstNodeOp::Program;

	p->append_child(some_statements);

	return p;
}
AstNode* AbstractSyntaxTree::gen_statements(AstNode* some_mkscope, 
	AstNode* some_list_statements, AstNode* some_rmscope)
{
	AstNode* p = mknode();
	p->op = AstNodeOp::Statements;
	p->append_child(some_mkscope);
	p->append_child(some_list_statements);
	p->append_child(some_rmscope);

	return p;
}
AstNode* AbstractSyntaxTree::gen_list_statement()
{
	AstNode* p = mknode();
	p->op = AstNodeOp::ListStatements;

	return p;
}
AstNode* AbstractSyntaxTree::gen_statement()
{
	AstNode* p = mknode();
	p->op = AstNodeOp::Statement;

	return p;
}
AstNode* AbstractSyntaxTree::gen_constant(int some_num)
{
	AstNode* p = mknode();
	p->op = AstNodeOp::Constant;
	p->num = some_num;

	return p;
}
AstNode* AbstractSyntaxTree::gen_ident(char* some_ident)
{
	AstNode* p = mknode();
	p->op = AstNodeOp::Ident;

	p->text.push_back(std::string(some_ident));

	return p;
}
AstNode* AbstractSyntaxTree::gen_mkscope()
{
	AstNode* p = mknode();
	p->op = AstNodeOp::MkScope;

	return p;
}
AstNode* AbstractSyntaxTree::gen_rmscope()
{
	AstNode* p = mknode();
	p->op = AstNodeOp::RmScope;

	return p;
}
AstNode* AbstractSyntaxTree::gen_assign(char* some_ident, 
	AstNode* some_expr)
{
	AstNode* ident_node = gen_ident(some_ident);

	AstNode* p = mknode();
	p->op = AstNodeOp::Assign;
	p->append_child(ident_node);
	p->append_child(some_expr);

	return p;
}
AstNode* AbstractSyntaxTree::gen_binop(char* some_op, AstNode* a, 
	AstNode* b)
{
	AstNode* p = mknode();
	p->op = AstNodeOp::Binop;
	p->append_child(a);
	p->append_child(b);

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


void AbstractSyntaxTree::print() const
{
	//printout("Beefs\n");
}

AstNode* AbstractSyntaxTree::mknode()
{
	std::unique_ptr<AstNode> p;
	p.reset(new AstNode());
	__nodes.push_back(std::move(p));
	return __nodes.back().get();
}
