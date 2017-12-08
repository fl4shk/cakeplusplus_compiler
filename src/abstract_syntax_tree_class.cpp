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
//AstNode* AbstractSyntaxTree::gen_var_decl(char* some_type_name, 
//	char* some_ident)
//{
//}
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
AstNode* AbstractSyntaxTree::gen_binop(char* some_op, AstNode* a, AstNode* b)
{
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
