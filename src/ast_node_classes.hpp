#ifndef ast_node_classes_hpp
#define ast_node_classes_hpp

#include "misc_includes.hpp"

//enum class AstNodeOp
//{
//	Program,
//	Statements,
//	ListStatement,
//	Statement,
//
//	Constant,
//	Ident,
//	//VarDecl,
//	MkScope, RmScope,
//	Assign,
//	Binop,
//
//	If, IfChain, While, DoWhile,
//};

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
	//AstNodeOp op;
	AstNodeBinop binop;
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

};


std::ostream& operator << (std::ostream& os, AstNode* to_print);


class AstProgram : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "program");
	}
};

class AstStatements : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "statements");
	}
};

class AstListStatement : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "list_statement");
	}
};


class AstStatement : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "statement");
	}
};

class AstConstant : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "constant(", num, ")");
	}
};


class AstIdent : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "ident(", text.front(), ")");
	}
};

class AstMkScope : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "mkscope");
	}
};

class AstRmScope : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "rmscope");
	}
};

class AstAssign : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "assign");
	}
};

class AstBinop : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "binop(", text.front(), ")");
	}
};

class AstIf : public AstNode
{
public:		// functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "if");
	}
};


class AstIfChain : public AstNode
{
public:		// functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "if_chain");
	}
};

class AstWhile : public AstNode
{
public:		// functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "while");
	}
};


class AstDoWhile : public AstNode
{
public:		// functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "do_while");
	}
};


#endif		// ast_node_classes_hpp
