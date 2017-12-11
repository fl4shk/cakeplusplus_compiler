#include "interpreter_class.hpp"

std::unique_ptr<Interpreter> interpreter(new Interpreter());


void Interpreter::interpret()
{
	printout("connected to dedicated RAM\n");
}


void Interpreter::visit_program(AstProgram* p)
{
}
void Interpreter::visit_statements(AstStatements* p)
{
}
void Interpreter::visit_list_statement(AstListStatement* p)
{
}
void Interpreter::visit_statement(AstStatement* p)
{
}
void Interpreter::visit_constant(AstConstant* p)
{
}
void Interpreter::visit_ident(AstIdent* p)
{
}
void Interpreter::visit_indexed_load(AstIndexedLoad* p)
{
}
void Interpreter::visit_mk_scope(AstMkScope* p)
{
}
void Interpreter::visit_rm_scope(AstRmScope* p)
{
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
