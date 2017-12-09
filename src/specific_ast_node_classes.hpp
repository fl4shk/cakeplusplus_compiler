#ifndef specific_ast_node_classes_hpp
#define specific_ast_node_classes_hpp


struct AstProgram : public AstNode
{
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "program");
	}

	inline auto statements()
	{
		return at(0);
	}
};

struct AstStatements : public AstNode
{
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

struct AstListStatement : public AstNode
{
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "list_statement");
	}
};


struct AstStatement : public AstNode
{
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "statement");
	}
};

struct AstConstant : public AstNode
{
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "constant(", num, ")");
	}
};


struct AstIdent : public AstNode
{
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "ident(", text.front(), ")");
	}
};

struct AstMkScope : public AstNode
{
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "mkscope");
	}
};

struct AstRmScope : public AstNode
{
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "rmscope");
	}
};

struct AstAssign : public AstNode
{
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

struct AstBinop : public AstNode
{
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

struct AstIf : public AstNode
{
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


struct AstIfChain : public AstNode
{
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

struct AstWhile : public AstNode
{
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


struct AstDoWhile : public AstNode
{
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

struct AstBuiltinTypename : public AstNode
{
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "builtin_typename(", text.front(), ")");
	}
};

struct AstVarDeclSimple : public AstNode
{
	virtual std::ostream& osprint(std::ostream& os)
	{
		return osprintout(os, "var_decl_simple");
	}

	inline auto builtin_typename_node()
	{
		return at(0);
	}
	inline auto ident_node()
	{
		return at(1);
	}
};


#endif		// specific_ast_node_classes_hpp
