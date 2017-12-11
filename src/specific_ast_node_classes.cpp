#include "specific_ast_node_classes.hpp"
#include "visitor_class.hpp"

void AstProgram::accept(Visitor* v)
{
	v->visit_program(this);
}

void AstStatements::accept(Visitor* v)
{
	v->visit_statements(this);
}

void AstListStatement::accept(Visitor* v)
{
	v->visit_list_statement(this);
}

void AstStatement::accept(Visitor* v)
{
	v->visit_statement(this);
}

void AstConstant::accept(Visitor* v)
{
	v->visit_constant(this);
}

void AstIdent::accept(Visitor* v)
{
	v->visit_ident(this);
}

void AstIndexedLoad::accept(Visitor* v)
{
	v->visit_indexed_load(this);
}

void AstMkScope::accept(Visitor* v)
{
	v->visit_mk_scope(this);
}

void AstRmScope::accept(Visitor* v)
{
	v->visit_rm_scope(this);
}

void AstAssign::accept(Visitor* v)
{
	v->visit_assign(this);
}

void AstIndexedAssign::accept(Visitor* v)
{
	v->visit_indexed_assign(this);
}

void AstBinop::accept(Visitor* v)
{
	v->visit_binop(this);
}

void AstIf::accept(Visitor* v)
{
	v->visit_if(this);
}

void AstIfChain::accept(Visitor* v)
{
	v->visit_if_chain(this);
}

void AstWhile::accept(Visitor* v)
{
	v->visit_while(this);
}

void AstDoWhile::accept(Visitor* v)
{
	v->visit_do_while(this);
}

void AstBuiltinTypename::accept(Visitor* v)
{
	v->visit_builtin_typename(this);
}

void AstVarDeclSimple::accept(Visitor* v)
{
	v->visit_var_decl_simple(this);
}

void AstVarDeclArray::accept(Visitor* v)
{
	v->visit_var_decl_array(this);
}

void AstVarDeclWithInit::accept(Visitor* v)
{
	v->visit_var_decl_with_init(this);
}
