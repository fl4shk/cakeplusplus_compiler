#include "abstract_syntax_tree_class.hpp"

AbstractSyntaxTree ast;


AbstractSyntaxTree::AbstractSyntaxTree()
{
	__nodes.next = &__nodes;
	__nodes.prev = &__nodes;

	__tree.next = &__tree;
	__tree.prev = &__tree;
}

AbstractSyntaxTree::~AbstractSyntaxTree()
{
	while (__nodes.next != &__nodes)
	{
		rmnode(__nodes.next);
	}

	while (__tree.next != &__tree)
	{
		rmtree(__tree.next);
	}
}

AstNode* AbstractSyntaxTree::gen_op_constant(int some_num)
{
}
AstNode* AbstractSyntaxTree::gen_op_ident(char* a)
{
}
AstNode* AbstractSyntaxTree::gen_op_var_decl(char* some_type_name, 
	char* some_ident)
{
}
AstNode* AbstractSyntaxTree::gen_op_mkscope()
{
}
AstNode* AbstractSyntaxTree::gen_op_rmscope()
{
}
AstNode* AbstractSyntaxTree::gen_op_block(AstNode* start_node, 
	AstNode* inner_node, AstNode* end_node)
{
}
AstNode* AbstractSyntaxTree::gen_op_assign(char* some_ident, 
	AstNode* some_expr)
{
}
AstNode* AbstractSyntaxTree::gen_op_binary(char* some_op, AstNode* a, 
	AstNode* b)
{
}
void AbstractSyntaxTree::prepend(AstNode* to_prepend)
{
	Tree* p = new Tree();
	p->start = to_prepend;

	__relink_tree(p, &__tree);
}

void AbstractSyntaxTree::print() const
{
	printout("Beefs\n");
}

