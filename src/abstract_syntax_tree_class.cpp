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
}
AstNode* AbstractSyntaxTree::gen_statements(AstNode* some_mkscope, 
	AstNode* some_list_statements, AstNode* some_rmscope)
{
}
AstNode* AbstractSyntaxTree::gen_list_statement()
{
}
AstNode* AbstractSyntaxTree::gen_statement()
{
}
AstNode* AbstractSyntaxTree::gen_constant(int some_num)
{
}
AstNode* AbstractSyntaxTree::gen_ident(char* a)
{
}
AstNode* AbstractSyntaxTree::gen_mkscope()
{
}
AstNode* AbstractSyntaxTree::gen_rmscope()
{
}
AstNode* AbstractSyntaxTree::gen_assign(char* some_ident, 
	AstNode* some_expr)
{
}
AstNode* AbstractSyntaxTree::gen_binop(char* some_op, AstNode* a, 
	AstNode* b)
{
	AstNode p;
	p.op = AstNodeOp::Binop;
	p.append_child(a);
	p.append_child(b);

	if (some_op == std::string("+"))
	{
		p.binop = AstNodeBinop::Plus;
	}
	else if (some_op == std::string("-"))
	{
		p.binop = AstNodeBinop::Minus;
	}
	else if (some_op == std::string("*"))
	{
		p.binop = AstNodeBinop::Multiplies;
	}
	else if (some_op == std::string("/"))
	{
		p.binop = AstNodeBinop::Divides;
	}
	else if (some_op == std::string("%"))
	{
		p.binop = AstNodeBinop::Modulo;
	}
	else if (some_op == std::string("=="))
	{
		p.binop = AstNodeBinop::CmpEq;
	}
	else if (some_op == std::string("!="))
	{
		p.binop = AstNodeBinop::CmpNe;
	}
	else if (some_op == std::string("<"))
	{
		p.binop = AstNodeBinop::CmpLt;
	}
	else if (some_op == std::string(">"))
	{
		p.binop = AstNodeBinop::CmpGt;
	}
	else if (some_op == std::string("<="))
	{
		p.binop = AstNodeBinop::CmpLe;
	}
	else if (some_op == std::string(">="))
	{
		p.binop = AstNodeBinop::CmpGe;
	}
	else if (some_op == std::string("&&"))
	{
		p.binop = AstNodeBinop::LogicAnd;
	}
	else if (some_op == std::string("||"))
	{
		p.binop = AstNodeBinop::LogicOr;
	}
	else if (some_op == std::string("&"))
	{
		p.binop = AstNodeBinop::BitAnd;
	}
	else if (some_op == std::string("|"))
	{
		p.binop = AstNodeBinop::BitOr;
	}
	else if (some_op == std::string("^"))
	{
		p.binop = AstNodeBinop::BitXor;
	}
	else if (some_op == std::string("<<"))
	{
		p.binop = AstNodeBinop::BitLsl;
	}
	else if (some_op == std::string(">>"))
	{
		p.binop = AstNodeBinop::BitLsr;
	}
	else if (some_op == std::string(">>>"))
	{
		p.binop = AstNodeBinop::BitAsr;
	}
	else
	{
		printerr("AbstractSyntaxTree::gen_binop():  Eek!\n");
		exit(1);
	}

	return mknode(p);
}


void AbstractSyntaxTree::print() const
{
	printout("Beefs\n");
}

AstNode* AbstractSyntaxTree::mknode(const AstNode& to_append)
{
	////AstNode* p = new AstNode();
	//*p = to_append;
	//p->next = &__tree;
	//(p->prev = __tree.prev)->next = p;
	//return(__tree.prev = p);

	std::unique_ptr<AstNode> ret;
	ret.reset(new AstNode());
	*ret = to_append;

	__nodes.push_back(std::move(ret));

	return __nodes.back().get();
}
