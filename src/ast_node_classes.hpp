#ifndef ast_node_classes_hpp
#define ast_node_classes_hpp

#include "misc_includes.hpp"

enum class AstNodeOp
{
	Program,
	Statements,
	ListStatements,
	Statement,

	Constant,
	Ident,
	VarDecl,
	MkScope,
	RmScope,
	Block,
	Assign,
	Binop,
};

// Binary operator ("+", "-", "*", "/", etc.)
enum class AstNodeBinop
{
	Plus,
	Minus,
	Multiplies,
	Divides,
	Modulo,
	CmpEq,
	CmpNe,
	CmpLt,
	CmpGt,
	CmpLe,
	CmpGe,
	LogicAnd,
	LogicOr,
	BitAnd,
	BitOr,
	BitXor,
	BitLsl,
	BitLsr,
	BitAsr,
};

class AstNode
{
public:		// variables and constants
	AstNodeOp op;
	AstNodeBinop binop;
	int num;
	std::vector<std::string> text;



	// The childrens
	std::vector<AstNode*> children;
	std::vector<AstNode*>& list = children;

public:		// functions
	AstNode();
	AstNode(const AstNode& to_copy) = default;
	AstNode(AstNode&& to_move) = default;
	virtual ~AstNode();

	AstNode& operator = (const AstNode& to_copy) = default;
	AstNode& operator = (AstNode&& to_move) = default;

	void append_child(AstNode* some_child);
	void append_to_list(AstNode* to_append);
};



#endif		// ast_node_classes_hpp
