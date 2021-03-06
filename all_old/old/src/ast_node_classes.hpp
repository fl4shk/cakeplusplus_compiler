#ifndef ast_node_classes_hpp
#define ast_node_classes_hpp

#include "misc_includes.hpp"
#include "symbol_table_class.hpp"
#include "liborangepower_src/json_stuff.hpp"

class Visitor;

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

	virtual void accept(Visitor* v);

	void append_child(AstNode* some_child);
	void append_to_list(AstNode* to_append);

	inline std::ostream& osprint(std::ostream& os) const
	{
		return osprintout(os, to_string());
	}

	virtual std::string to_string() const
	{
		printerr("AstNode::to_string():  Eek!\n");
		exit(1);
		return std::string("");
	}

	void output_to_json(Json::Value& json_node) const;

protected:		// functions
	inline AstNode* at(size_t index)
	{
		return children.at(index);
	}

};


std::ostream& operator << (std::ostream& os, AstNode* to_print);

#include "specific_ast_node_classes.hpp"


#endif		// ast_node_classes_hpp
