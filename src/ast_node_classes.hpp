#ifndef ast_node_classes_hpp
#define ast_node_classes_hpp

#include "misc_includes.hpp"

enum class AstNodeOp
{
	Statements,
	ListStatements,

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


	std::vector<AstNode*> list;

public:		// functions
	AstNode();
	virtual ~AstNode();

	void append_child(AstNode* some_child);
	void append_to_list(AstNode* to_append);
};



#endif		// ast_node_classes_hpp
