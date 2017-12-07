#include "ast_node_classes.hpp"


AstNode::AstNode()
{
}
AstNode::~AstNode()
{
}


void AstNode::append_child(AstNode* some_child)
{
	if (children.count(some_child) != 0)
	{
		printerr("AstNode::append_child():  Eek!\n");
		exit(1);
	}

	children.insert(some_child);
}
