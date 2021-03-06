#ifndef specific_ast_node_classes_hpp
#define specific_ast_node_classes_hpp

#include "ast_node_classes.hpp"

class Visitor;

struct AstProgram : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("program");
	}

	inline auto statements() { return at(0); }
};

struct AstStatements : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("statements");
	}

	inline auto mkscope() { return at(0); }
	inline auto list_statement() { return at(1); }
	inline auto rmscope() { return at(2); }
};

struct AstListStatement : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("list_statement");
	}
};


struct AstListIdent : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("list_ident");
	}
};


struct AstConstant : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("constant(", num, ")");
	}
};


struct AstIdent : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("ident(", text.front(), ")");
	}
};

struct AstLoad : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("load");
	}

	inline auto ident_node() { return at(0); }
};
struct AstIndexedLoad : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("indexed_load");
	}

	inline auto ident_node() { return at(0); }
	inline auto index_node() { return at(1); }
};

struct AstMkScope : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("mkscope");
	}
};

struct AstRmScope : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("rmscope");
	}
};

struct AstAssign : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("assign");
	}

	inline auto ident_node() { return at(0); }
	inline auto expr() { return at(1); }
};

struct AstIndexedAssign : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("indexed_assign");
	}

	inline auto ident_node() { return at(0); }
	inline auto index_node() { return at(1); }
	inline auto rhs_node() { return at(2); }
};

struct AstBinop : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("binop(", text.front(), ")");
	}

	inline auto arg_a() { return at(0); }
	inline auto arg_b() { return at(1); }
};

struct AstIf : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("if");
	}

	inline auto expr() { return at(0); }
	inline auto statement() { return at(1); }
};


struct AstIfChain : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("if_chain");
	}

	inline auto expr() { return at(0); }
	inline auto statement_if() { return at(1); }
	inline auto statement_else() { return at(2); }
};

struct AstWhile : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("while");
	}

	inline auto expr() { return at(0); }
	inline auto statement() { return at(1); }

};


struct AstDoWhile : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("do_while");
	}

	inline auto statement() { return at(0); }
	inline auto expr() { return at(1); }
};

struct AstBuiltinTypename : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("builtin_typename(", text.front(), ")");
	}
};

struct AstVarDeclSimple : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("var_decl_simple");
	}

	inline auto builtin_typename_node() { return at(0); }
	inline auto ident_node() { return at(1); }
};

struct AstVarDeclArray : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("var_decl_array");
	}

	inline auto builtin_typename_node() { return at(0); }
	inline auto ident_node() { return at(1); }
	inline auto dim_node() { return at(2); }
};

struct AstVarDeclWithInit : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("var_decl_with_init");
	}

	inline auto builtin_typename_node() { return at(0); }
	inline auto ident_node() { return at(1); }
	inline auto expr() { return at(2); }

};

struct AstMultiVarDecl : public AstNode
{
	void accept(Visitor* v);
	std::string to_string() const
	{
		return sconcat("multi_var_decl");
	}

	inline auto builtin_typename_node() { return at(0); }
};


#endif		// specific_ast_node_classes_hpp
