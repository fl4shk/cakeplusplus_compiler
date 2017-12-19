#include "abstract_syntax_tree_classes.hpp"
#include "symbol_table_classes.hpp"


AstNode::AstNode()
{
}

AstNode::AstNode(AstOp s_op, std::deque<AstNode*>&& s_children)
	: op(s_op), children(std::move(s_children))
{
}
AstNode::~AstNode()
{
}

