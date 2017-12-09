#include "ast_node_classes.hpp"


AstNode::AstNode()
{
}
AstNode::~AstNode()
{
}

void AstNode::append_child(AstNode* some_child)
{
	for (AstNode* iter : children)
	{
		if (iter == some_child)
		{
			printerr("AstNode::append_child():  Eek!\n");
			exit(1);
		}
	}

	children.push_back(some_child);
}

//void AstNode::append_next(AstNode* some_next);
//{
//	if (has_next())
//	{
//		printerr("AstNode::append_next():  Eek!\n");
//		exit(1);
//	}
//	next = some_next;
//}

void AstNode::append_to_list(AstNode* to_append)
{
	for (AstNode* iter : list)
	{
		if (iter == to_append)
		{
			printerr("AstNode::append_to_list():  Eek!\n");
		}
	}

	list.push_back(to_append);
}


//std::ostream& operator << (std::ostream& os, AstNode* to_print)
//{
//}
