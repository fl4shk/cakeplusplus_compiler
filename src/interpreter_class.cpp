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
	push_ident(&p->text.front());
}
void Interpreter::visit_load(AstLoad* p)
{
	p->ident_node()->accept(this);
	auto ident_str = pop_ident();
	auto sym = sym_tbl.find(*ident_str);
	if (sym == nullptr)
	{
		printerr("visit_load():  No symbol with name \"",
			*ident_str, "\"\n");
		exit(1);
	}
}
void Interpreter::visit_indexed_load(AstIndexedLoad* p)
{
	p->ident_node()->accept(this);
	auto ident_str = pop_ident();
	auto sym = sym_tbl.find(*ident_str);
	if (sym == nullptr)
	{
		printerr("visit_indexed_load():  No symbol with name \"",
			*ident_str, "\"\n");
		exit(1);
	}

	p->index_node()->accept(this);
	const auto index = pop_num();

	if ((u32)index > sym->data().size())
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
}
void Interpreter::visit_indexed_assign(AstIndexedAssign* p)
{
}
void Interpreter::visit_binop(AstBinop* p)
{
}
void Interpreter::visit_if(AstIf* p)
{
}
void Interpreter::visit_if_chain(AstIfChain* p)
{
}
void Interpreter::visit_while(AstWhile* p)
{
}
void Interpreter::visit_do_while(AstDoWhile* p)
{
}
void Interpreter::visit_builtin_typename(AstBuiltinTypename* p)
{
}
void Interpreter::visit_var_decl_simple(AstVarDeclSimple* p)
{
}
void Interpreter::visit_var_decl_array(AstVarDeclArray* p)
{
}
void Interpreter::visit_var_decl_with_init(AstVarDeclWithInit* p)
{
}
