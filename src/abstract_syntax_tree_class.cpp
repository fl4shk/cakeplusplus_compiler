#include "abstract_syntax_tree_class.hpp"

AbstractSyntaxTree ast;


AbstractSyntaxTree::AbstractSyntaxTree()
{
}

AbstractSyntaxTree::~AbstractSyntaxTree()
{
}


AstNode* AbstractSyntaxTree::gen_program(AstNode* some_statements)
{
	auto p = mknode<AstProgram>();

	p->append_child(some_statements);

	if (__program != nullptr)
	{
		printerr("AbstractSyntaxTree::gen_program():  Eek!\n");
		exit(1);
	}
	__program = p;

	return p;
}
AstNode* AbstractSyntaxTree::gen_statements(AstNode* some_mkscope, 
	AstNode* some_list_statement, AstNode* some_rmscope)
{
	auto p = mknode<AstStatements>();
	p->append_child(some_mkscope);
	p->append_child(some_list_statement);
	p->append_child(some_rmscope);

	return p;
}
AstNode* AbstractSyntaxTree::gen_list_statement()
{
	auto p = mknode<AstListStatement>();

	return p;
}
AstNode* AbstractSyntaxTree::gen_statement()
{
	auto p = mknode<AstStatement>();

	return p;
}
AstNode* AbstractSyntaxTree::gen_constant(int some_num)
{
	auto p = mknode<AstConstant>();
	p->num = some_num;

	return p;
}
AstNode* AbstractSyntaxTree::gen_ident(const char* some_ident)
{
	auto p = mknode<AstIdent>();
	//printout("AbstractSyntaxTree::gen_ident():  ", some_ident, "\n");

	p->text.push_back(std::string(some_ident));

	return p;
}
AstNode* AbstractSyntaxTree::gen_mkscope()
{
	auto p = mknode<AstMkScope>();

	return p;
}
AstNode* AbstractSyntaxTree::gen_rmscope()
{
	auto p = mknode<AstRmScope>();

	return p;
}
AstNode* AbstractSyntaxTree::gen_assign(const char* some_ident, 
	AstNode* some_expr)
{
	auto ident_node = gen_ident(some_ident);

	auto p = mknode<AstAssign>();
	p->append_child(ident_node);
	p->append_child(some_expr);

	return p;
}
AstNode* AbstractSyntaxTree::gen_binop(const char* some_op, AstNode* a, 
	AstNode* b)
{
	auto p = mknode<AstBinop>();
	p->text.push_back(some_op);
	p->append_child(a);
	p->append_child(b);

	//printout("AbstractSyntaxTree::gen_binop():  some_op ==  ", some_op,
	//	"\n");

	if (some_op == std::string("+"))
	{
		p->binop = AstNodeBinop::Plus;
	}
	else if (some_op == std::string("-"))
	{
		p->binop = AstNodeBinop::Minus;
	}
	else if (some_op == std::string("*"))
	{
		p->binop = AstNodeBinop::Multiplies;
	}
	else if (some_op == std::string("/"))
	{
		p->binop = AstNodeBinop::Divides;
	}
	else if (some_op == std::string("%"))
	{
		p->binop = AstNodeBinop::Modulo;
	}
	else if (some_op == std::string("=="))
	{
		p->binop = AstNodeBinop::CmpEq;
	}
	else if (some_op == std::string("!="))
	{
		p->binop = AstNodeBinop::CmpNe;
	}
	else if (some_op == std::string("<"))
	{
		p->binop = AstNodeBinop::CmpLt;
	}
	else if (some_op == std::string(">"))
	{
		p->binop = AstNodeBinop::CmpGt;
	}
	else if (some_op == std::string("<="))
	{
		p->binop = AstNodeBinop::CmpLe;
	}
	else if (some_op == std::string(">="))
	{
		p->binop = AstNodeBinop::CmpGe;
	}
	else if (some_op == std::string("&&"))
	{
		p->binop = AstNodeBinop::LogicAnd;
	}
	else if (some_op == std::string("||"))
	{
		p->binop = AstNodeBinop::LogicOr;
	}
	else if (some_op == std::string("&"))
	{
		p->binop = AstNodeBinop::BitAnd;
	}
	else if (some_op == std::string("|"))
	{
		p->binop = AstNodeBinop::BitOr;
	}
	else if (some_op == std::string("^"))
	{
		p->binop = AstNodeBinop::BitXor;
	}
	else if (some_op == std::string("<<"))
	{
		p->binop = AstNodeBinop::BitLsl;
	}
	else if (some_op == std::string(">>"))
	{
		p->binop = AstNodeBinop::BitLsr;
	}
	else if (some_op == std::string(">>>"))
	{
		p->binop = AstNodeBinop::BitAsr;
	}
	else
	{
		printerr("AbstractSyntaxTree::gen_binop():  Eek!\n");
		exit(1);
	}

	return p;
}

AstNode* AbstractSyntaxTree::gen_if_statement(AstNode* some_expr, 
	AstNode* some_statement)
{
	auto p = mknode<AstIf>();

	p->append_child(some_expr);
	p->append_child(some_statement);

	return p;
}
AstNode* AbstractSyntaxTree::gen_if_chain_statement(AstNode* some_expr,
	AstNode* some_statement_if, AstNode* some_statement_else)
{
	auto p = mknode<AstIfChain>();

	p->append_child(some_expr);
	p->append_child(some_statement_if);
	p->append_child(some_statement_else);

	return p;
}
AstNode* AbstractSyntaxTree::gen_while_statement(AstNode* some_expr,
	AstNode* some_statement)
{
	auto p = mknode<AstWhile>();

	p->append_child(some_expr);
	p->append_child(some_statement);

	return p;
}
AstNode* AbstractSyntaxTree::gen_do_while_statement
	(AstNode* some_statement, AstNode* some_expr)
{
	auto p = mknode<AstDoWhile>();

	p->append_child(some_statement);
	p->append_child(some_expr);

	return p;
}

AstNode* AbstractSyntaxTree::gen_builtin_typename
	(const char* some_type_name)
{
	auto p = mknode<AstBuiltinTypename>();
	p->text.push_back(some_type_name);

	if (some_type_name == "u8")
	{
		p->builtin_typename = BuiltinTypename::U8;
	}
	else if (some_type_name == "u16")
	{
		p->builtin_typename = BuiltinTypename::U16;
	}
	else if (some_type_name == "u32")
	{
		p->builtin_typename = BuiltinTypename::U32;
	}
	else if (some_type_name == "u64")
	{
		p->builtin_typename = BuiltinTypename::U64;
	}
	else if (some_type_name == "s8")
	{
		p->builtin_typename = BuiltinTypename::S8;
	}
	else if (some_type_name == "s16")
	{
		p->builtin_typename = BuiltinTypename::S16;
	}
	else if (some_type_name == "s32")
	{
		p->builtin_typename = BuiltinTypename::S32;
	}
	else if (some_type_name == "s64")
	{
		p->builtin_typename = BuiltinTypename::S64;
	}
	else
	{
		printerr("AbstractSyntaxTree::gen_builtin_typename():  Eek!\n");
		exit(1);
	}

	return p;
}
AstNode* AbstractSyntaxTree::gen_var_decl_simple
	(const char* some_type_name, const char* some_ident)
{
	auto builtin_typename_node 
		= gen_builtin_typename(some_type_name);
	auto ident_node = gen_ident(some_ident);
	auto p = mknode<AstVarDeclSimple>();

	p->append_child(builtin_typename_node);
	p->append_child(ident_node);

	return p;
}

