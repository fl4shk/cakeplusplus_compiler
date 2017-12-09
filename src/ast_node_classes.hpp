#ifndef ast_node_classes_hpp
#define ast_node_classes_hpp

#include "misc_includes.hpp"
#include "symbol_table_class.hpp"

// Binary operator ("+", "-", "*", "/", etc.)
enum class AstNodeBinop : int
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
	//AstNodeOp op;
	union
	{
		AstNodeBinop binop;
		BuiltinTypename builtin_typename;
	};
	int num;
	std::vector<std::string> text;



	// The childrens
	std::vector<AstNode*> children;

	// I don't think any nodes that are lists will have childrens.
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

	virtual std::ostream& osprint(std::ostream& os)
	{
		printerr("AstNode::osprint():  Eek!\n");
		exit(1);
		return os;
	}

protected:		// functions
	inline AstNode* at(size_t index)
	{
		return children.at(index);
	}

};


std::ostream& operator << (std::ostream& os, AstNode* to_print);

#include "specific_ast_node_classes.hpp"


#endif		// ast_node_classes_hpp
