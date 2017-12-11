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
	__num_stack.push(p->num);
}
void Interpreter::visit_ident(AstIdent* p)
{
	//__ident_stack.push(&p->text.front());
	__ident_str = &p->text.front();
}
void Interpreter::visit_load(AstLoad* p)
{
	p->ident_node()->accept(this);
	//__num_stack.push();
}
void Interpreter::visit_indexed_load(AstIndexedLoad* p)
{
	printerr("Interpreter::visit_indexed_load() is incomplete!\n");
	exit(1);

	p->ident_node()->accept(this);
	p->index_node()->accept(this);

	//__num_stack.push();
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
