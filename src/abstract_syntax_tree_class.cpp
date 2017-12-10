#include "abstract_syntax_tree_class.hpp"
#include "misc_bison_stuff.hpp"

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
	//if (some_num == nullptr)
	//{
	//	printerr("AbstractSyntaxTree::gen_constant():  Eek!\n");
	//	exit(1);
	//}

	auto p = mknode<AstConstant>();
	p->num = some_num;

	return p;
}
AstNode* AbstractSyntaxTree::gen_ident(const char* some_ident)
{
	auto p = mknode<AstIdent>();
	//printout("AbstractSyntaxTree::gen_ident():  ", some_ident_node, "\n");

	p->text.push_back(std::string(some_ident));

	return p;
}

AstNode* AbstractSyntaxTree::gen_indexed_load(AstNode* some_ident_node, 
	AstNode* some_index)
{
	//auto some_ident_node = gen_ident(some_ident_node);

	auto p = mknode<AstIndexedLoad>();
	p->append_child(some_ident_node);
	p->append_child(some_index);

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
AstNode* AbstractSyntaxTree::gen_assign(AstNode* some_ident_node, 
	AstNode* some_expr)
{
	//auto some_ident_node = gen_ident(some_ident_node);

	auto p = mknode<AstAssign>();
	p->append_child(some_ident_node);
	p->append_child(some_expr);

	return p;
}
AstNode* AbstractSyntaxTree::gen_indexed_assign(AstNode* some_ident_node,
	AstNode* some_index, AstNode* some_rhs)
{
	//auto some_ident_node = gen_ident(some_ident_node);

	auto p = mknode<AstIndexedAssign>();
	p->append_child(some_ident_node);
	p->append_child(some_index);
	p->append_child(some_rhs);

	return p;
}
AstNode* AbstractSyntaxTree::gen_finished_binop
	(AstNode* some_incomplete_binop, AstNode* a, AstNode* b)
{
	auto p = some_incomplete_binop;
	if (p->text.front() == std::string("+"))
	{
		p->binop = AstNodeBinop::Plus;
	}
	else if (p->text.front() == std::string("-"))
	{
		p->binop = AstNodeBinop::Minus;
	}
	else if (p->text.front() == std::string("*"))
	{
		p->binop = AstNodeBinop::Multiplies;
	}
	else if (p->text.front() == std::string("/"))
	{
		p->binop = AstNodeBinop::Divides;
	}
	else if (p->text.front() == std::string("%"))
	{
		p->binop = AstNodeBinop::Modulo;
	}
	else if (p->text.front() == std::string("=="))
	{
		p->binop = AstNodeBinop::CmpEq;
	}
	else if (p->text.front() == std::string("!="))
	{
		p->binop = AstNodeBinop::CmpNe;
	}
	else if (p->text.front() == std::string("<"))
	{
		p->binop = AstNodeBinop::CmpLt;
	}
	else if (p->text.front() == std::string(">"))
	{
		p->binop = AstNodeBinop::CmpGt;
	}
	else if (p->text.front() == std::string("<="))
	{
		p->binop = AstNodeBinop::CmpLe;
	}
	else if (p->text.front() == std::string(">="))
	{
		p->binop = AstNodeBinop::CmpGe;
	}
	else if (p->text.front() == std::string("&&"))
	{
		p->binop = AstNodeBinop::LogicAnd;
	}
	else if (p->text.front() == std::string("||"))
	{
		p->binop = AstNodeBinop::LogicOr;
	}
	else if (p->text.front() == std::string("&"))
	{
		p->binop = AstNodeBinop::BitAnd;
	}
	else if (p->text.front() == std::string("|"))
	{
		p->binop = AstNodeBinop::BitOr;
	}
	else if (p->text.front() == std::string("^"))
	{
		p->binop = AstNodeBinop::BitXor;
	}
	else if (p->text.front() == std::string("<<"))
	{
		p->binop = AstNodeBinop::BitLsl;
	}
	else if (p->text.front() == std::string(">>"))
	{
		p->binop = AstNodeBinop::BitLsr;
	}
	else if (p->text.front() == std::string(">>>"))
	{
		p->binop = AstNodeBinop::BitAsr;
	}
	else
	{
		printerr("ast():  Eek!\n");
		exit(1);
	}
	p->append_child(a);
	p->append_child(b);

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
	(char* some_typename_node)
{
	auto p = mknode<AstBuiltinTypename>();
	p->text.push_back(std::string(some_typename_node));

	if (some_typename_node == std::string("u8"))
	{
		p->builtin_typename = BuiltinTypename::U8;
	}
	else if (some_typename_node == std::string("u16"))
	{
		p->builtin_typename = BuiltinTypename::U16;
	}
	else if (some_typename_node == std::string("u32"))
	{
		p->builtin_typename = BuiltinTypename::U32;
	}
	else if (some_typename_node == std::string("u64"))
	{
		p->builtin_typename = BuiltinTypename::U64;
	}
	else if (some_typename_node == std::string("s8"))
	{
		p->builtin_typename = BuiltinTypename::S8;
	}
	else if (some_typename_node == std::string("s16"))
	{
		p->builtin_typename = BuiltinTypename::S16;
	}
	else if (some_typename_node == std::string("s32"))
	{
		p->builtin_typename = BuiltinTypename::S32;
	}
	else if (some_typename_node == std::string("s64"))
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
	(AstNode* some_typename_node, AstNode* some_ident_node)
{
	//auto some_typename_node = gen_builtin_typename(some_typename_node);
	//auto some_ident_node = gen_ident(some_ident_node);
	auto p = mknode<AstVarDeclSimple>();

	p->append_child(some_typename_node);
	p->append_child(some_ident_node);

	return p;
}


AstNode* AbstractSyntaxTree::gen_var_decl_array
	(AstNode* some_typename_node, AstNode* some_ident_node, 
	AstNode* some_dim_node)
{
	auto p = mknode<AstVarDeclArray>();

	p->append_child(some_typename_node);
	p->append_child(some_ident_node);
	p->append_child(some_dim_node);

	return p;
}

AstNode* AbstractSyntaxTree::gen_var_decl_with_init
	(AstNode* some_typename_node, AstNode* some_ident_node, 
	AstNode* some_expr)
{
	//auto some_typename_node = gen_builtin_typename(some_typename_node);
	//auto some_ident_node = gen_ident(some_ident_node);
	auto p = mknode<AstVarDeclWithInit>();

	p->append_child(some_typename_node);
	p->append_child(some_ident_node);
	p->append_child(some_expr);

	return p;
}


extern "C"
{
extern const char* cstm_strdup(char* some_c_str);
extern const int* cstm_intdup(int num);

YYSTYPE ast_gen_builtin_typename(char* some_typename)
{
	return ast.gen_builtin_typename(some_typename);
}
YYSTYPE ast_gen_ident(char* some_ident)
{
	return ast.gen_ident(some_ident);
}
YYSTYPE ast_gen_constant(int some_num)
{
	return ast.gen_constant(some_num);
}
YYSTYPE ast_gen_initial_binop(char* some_op)
{
	auto p = ast.make_initial_binop_node();
	p->text.push_back(std::string(some_op));

	return p;
}

}
