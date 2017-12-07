#ifndef ast_node_classes_hpp
#define ast_node_classes_hpp

#include "misc_includes.hpp"

enum class AstNodeOp
{
	Constant,
	Ident,
	VarDecl,
	MkScope,
	RmScope,
	Block,
	Assign,
	Binary,
};

class AstNode
{
public:		// variables
	AstNodeOp op;
	int num;
	std::vector<std::string> text;


	// The childrens
	std::set<AstNode*> children;

	// Circular linked list links
	AstNode * next, * prev;

public:		// functions
	AstNode();
	virtual ~AstNode();

	void append_child(AstNode* some_child);
};



#endif		// ast_node_classes_hpp
