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

AstNodeBase* AbstractSyntaxTree::gen_op_mkscope()
{
}
AstNodeBase* AbstractSyntaxTree::gen_op_rmscope()
{
}
AstNodeBase* AbstractSyntaxTree::gen_op_var_decl
	(char* some_type_name, char* some_ident)
{
}
AstNodeBase* AbstractSyntaxTree::gen_op_assign
	(char* some_ident, AstNodeBase* some_expr)
{
}
AstNodeBase* AbstractSyntaxTree::gen_op_constant(int some_num)
{
}
AstNodeBase* AbstractSyntaxTree::gen_op_binary(char* some_op, 
	AstNodeBase* a, AstNodeBase* b)
{
}
AstNodeBase* AbstractSyntaxTree::gen_op_block(AstNodeBase* start_node, 
	AstNodeBase* inner_node, AstNodeBase* end_node)
{
}
AstNodeBase* AbstractSyntaxTree::gen_op_ident(char* a)
{
}
void AbstractSyntaxTree::prepend(AstNodeBase* to_prepend)
{
	Tree* p = new Tree();
	p->start = to_prepend;

	__relink_tree(p, &__tree);
}

void AbstractSyntaxTree::print() const
{
	printout("Beefs\n");
}

