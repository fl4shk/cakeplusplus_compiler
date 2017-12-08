#include "abstract_syntax_tree_class.hpp"

AbstractSyntaxTree ast;


AbstractSyntaxTree::AbstractSyntaxTree()
{
}

AbstractSyntaxTree::~AbstractSyntaxTree()
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
