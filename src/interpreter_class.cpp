#include "interpreter_class.hpp"

Interpreter interpreter;


void Interpreter::interpret()
{
	printout("connected to dedicated RAM\n");
	ast.program()->accept(this);
}


void Interpreter::visit_program(AstProgram* p)
{
	p->statements()->accept(this);
}
void Interpreter::visit_statements(AstStatements* p)
{
	p->mkscope()->accept(this);
	p->list_statement()->accept(this);
	p->rmscope()->accept(this);
}
void Interpreter::visit_list_statement(AstListStatement* p)
{
	for (auto iter : p->list)
	{
		iter->accept(this);
	}
}
void Interpreter::visit_constant(AstConstant* p)
{
	push_num(p->num);
}
void Interpreter::visit_ident(AstIdent* p)
{
	push_str(&p->text.front());
}
void Interpreter::visit_load(AstLoad* p)
{
	p->ident_node()->accept(this);
	auto ident_str = pop_str();
	auto sym = sym_tbl.find(*ident_str);
	if (sym == nullptr)
	{
		printerr("visit_load():  No symbol with name \"",
			*ident_str, "\"\n");
		exit(1);
	}

	if (0 >= sym->data().size())
	{
		printerr("visit_load():  Eek!\n");
		exit(1);
	}

	push_num(sym->data().front());
}
void Interpreter::visit_indexed_load(AstIndexedLoad* p)
{
	p->ident_node()->accept(this);
	auto ident_str = pop_str();
	auto sym = sym_tbl.find(*ident_str);
	if (sym == nullptr)
	{
		printerr("visit_indexed_load():  No symbol with name \"",
			*ident_str, "\"\n");
		exit(1);
	}

	p->index_node()->accept(this);
	const auto index = pop_num();

	if ((index < 0) || ((u32)index >= sym->data().size()))
	{
		printerr("visit_indexed_load():  Index ", index, 
			" out of range!\n");
		exit(1);
	}

	push_num(sym->data().at(index));
}
void Interpreter::visit_mk_scope(AstMkScope* p)
{
	sym_tbl.mkscope();
}
void Interpreter::visit_rm_scope(AstRmScope* p)
{
	sym_tbl.rmscope();
}
void Interpreter::visit_assign(AstAssign* p)
{
	p->ident_node()->accept(this);
	auto ident_str = pop_str();
	auto sym = sym_tbl.find(*ident_str);
	if (sym == nullptr)
	{
		printerr("visit_assign():  No symbol with name \"",
			*ident_str, "\"\n");
		exit(1);
	}

	p->expr()->accept(this);
	const auto expr = pop_num();

	printout("Assigning ", expr, " to \"", *ident_str, "\"\n");
	sym->data().front() = expr;
}

void Interpreter::visit_indexed_assign(AstIndexedAssign* p)
{
	p->ident_node()->accept(this);
	auto ident_str = pop_str();
	auto sym = sym_tbl.find(*ident_str);
	if (sym == nullptr)
	{
		printerr("visit_indexed_assign():  No symbol with name \"",
			*ident_str, "\"\n");
		exit(1);
	}

	p->index_node()->accept(this);
	const auto index = pop_num();

	if ((index < 0) || ((u32)index >= sym->data().size()))
	{
		printerr("visit_indexed_assign():  Index ", index, 
			" out of range!\n");
		exit(1);
	}

	p->rhs_node()->accept(this);
	const auto rhs = pop_num();

	printout("Assigning ", rhs, " to \"", *ident_str, 
		"\" at index ", index, "\n");
	sym->data().at(index) = rhs;
}
void Interpreter::visit_binop(AstBinop* p)
{
	p->arg_a()->accept(this);
	const auto a = pop_num();

	p->arg_b()->accept(this);
	const auto b = pop_num();

	const u32 temp_a = a, temp_b = b;
	const u32 temp_c = temp_a >> temp_b;

	switch (p->binop)
	{
		case AstNodeBinop::Plus:
			push_num(a + b);
			break;
		case AstNodeBinop::Minus:
			push_num(a - b);
			break;
		case AstNodeBinop::Multiplies:
			push_num(a * b);
			break;
		case AstNodeBinop::Divides:
			push_num(a / b);
			break;
		case AstNodeBinop::Modulo:
			push_num(a % b);
			break;
		case AstNodeBinop::CmpEq:
			push_num(a == b);
			break;
		case AstNodeBinop::CmpNe:
			push_num(a != b);
			break;
		case AstNodeBinop::CmpLt:
			push_num(a < b);
			break;
		case AstNodeBinop::CmpGt:
			push_num(a > b);
			break;
		case AstNodeBinop::CmpLe:
			push_num(a <= b);
			break;
		case AstNodeBinop::CmpGe:
			push_num(a >= b);
			break;
		case AstNodeBinop::LogicAnd:
			push_num(a && b);
			break;
		case AstNodeBinop::LogicOr:
			push_num(a || b);
			break;
		case AstNodeBinop::BitAnd:
			push_num(a & b);
			break;
		case AstNodeBinop::BitOr:
			push_num(a | b);
			break;
		case AstNodeBinop::BitXor:
			push_num(a ^ b);
			break;
		case AstNodeBinop::BitLsl:
			push_num(a << b);
			break;
		case AstNodeBinop::BitLsr:
			push_num(temp_c);
			break;
		case AstNodeBinop::BitAsr:
			push_num(a >> b);
			break;
		default:
			printerr("Interpreter::visit_binop():  Eek!\n");
			exit(1);
			break;
	}
}
void Interpreter::visit_if(AstIf* p)
{
	p->expr()->accept(this);
	const auto expr = pop_num();

	if (expr)
	{
		p->statement()->accept(this);
	}
}
void Interpreter::visit_if_chain(AstIfChain* p)
{
	p->expr()->accept(this);
	const auto expr = pop_num();

	if (expr)
	{
		p->statement_if()->accept(this);
	}
	else
	{
		p->statement_else()->accept(this);
	}
}
void Interpreter::visit_while(AstWhile* p)
{
	int expr;

	for (;;)
	{
		p->expr()->accept(this);
		expr = pop_num();

		if (!expr)
		{
			break;
		}

		p->statement()->accept(this);
	}
}
void Interpreter::visit_do_while(AstDoWhile* p)
{
	int expr;

	do
	{
		p->statement()->accept(this);

		p->expr()->accept(this);
		expr = pop_num();
	} while (expr);
}
void Interpreter::visit_builtin_typename(AstBuiltinTypename* p)
{
	//push_str(&p->text.front());
}
void Interpreter::visit_var_decl_simple(AstVarDeclSimple* p)
{
	//switch (p->builtin_typename_node()->builtin_typename)
	p->builtin_typename_node()->accept(this);

	p->ident_node()->accept(this);
	auto ident_str = pop_str();

	auto sym = sym_tbl.find_in_this_level(*ident_str);

	if (sym != nullptr)
	{
		printerr("visit_var_decl_simple():  ",
			"There is already a symbol with name \"", ident_str,
			"\"!\n");
		exit(1);
	}

	Symbol to_insert_or_assign(*ident_str, SymType::VarName);
	to_insert_or_assign.data().push_back(0);
	sym_tbl.insert_or_assign(std::move(to_insert_or_assign));
}
void Interpreter::visit_var_decl_array(AstVarDeclArray* p)
{
	//switch (p->builtin_typename_node()->builtin_typename)
	p->builtin_typename_node()->accept(this);

	p->ident_node()->accept(this);
	auto ident_str = pop_str();

	auto sym = sym_tbl.find_in_this_level(*ident_str);

	if (sym != nullptr)
	{
		printerr("visit_var_decl_simple():  ",
			"There is already a symbol with name \"", ident_str,
			"\"!\n");
		exit(1);
	}

	p->dim_node()->accept(this);
	const auto dim = pop_num();
	if (dim <= 0)
	{
		printerr("visit_var_decl_simple():  Can't have an array ",
			"dimension smaller than 1!\n");
		exit(1);
	}

	Symbol to_insert_or_assign(*ident_str, SymType::VarName);

	for (int i=0; i<dim; ++i)
	{
		to_insert_or_assign.data().push_back(0);
	}
	sym_tbl.insert_or_assign(std::move(to_insert_or_assign));
}
void Interpreter::visit_var_decl_with_init(AstVarDeclWithInit* p)
{
}
