#ifndef ast_node_classes_hpp
#define ast_node_classes_hpp

#include "misc_includes.hpp"

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

protected:		// functions
	inline AstNode* at(size_t index)
	{
		return children.at(index);
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

	inline auto statements()
	{
		return at(0);
	}
};

class AstStatements : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "statements");
	}

	inline auto mkscope()
	{
		return at(0);
	}
	inline auto list_statement()
	{
		return at(1);
	}
	inline auto rmscope()
	{
		return at(2);
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

	inline auto ident_node()
	{
		return at(0);
	}
	inline auto expr()
	{
		return at(1);
	}
};

class AstBinop : public AstNode
{
public:		// Functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "binop(", text.front(), ")");
	}

	inline auto arg_a()
	{
		return at(0);
	}
	inline auto arg_b()
	{
		return at(1);
	}
};

class AstIf : public AstNode
{
public:		// functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "if");
	}

	inline auto expr()
	{
		return at(0);
	}
	inline auto statement()
	{
		return at(1);
	}
};


class AstIfChain : public AstNode
{
public:		// functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "if_chain");
	}

	inline auto expr()
	{
		return at(0);
	}
	inline auto statement_if()
	{
		return at(1);
	}
	inline auto statement_else()
	{
		return at(2);
	}
};

class AstWhile : public AstNode
{
public:		// functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "while");
	}

	inline auto expr()
	{
		return at(0);
	}
	inline auto statement()
	{
		return at(1);
	}

};


class AstDoWhile : public AstNode
{
public:		// functions
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "do_while");
	}

	inline auto statement()
	{
		return at(0);
	}
	inline auto expr()
	{
		return at(1);
	}
};


#endif		// ast_node_classes_hpp
