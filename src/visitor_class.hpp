#ifndef visitor_class_hpp
#define visitor_class_hpp

#include "ast_node_classes.hpp"
#include "specific_ast_node_classes.hpp"

class Visitor
{
protected:		// variables
	

public:		// functions
	virtual ~Visitor()
	{
	}

	virtual void visit_program(AstProgram* p) = 0;
	virtual void visit_statements(AstStatements* p) = 0;
	virtual void visit_list_statement(AstListStatement* p) = 0;
	virtual void visit_constant(AstConstant* p) = 0;
	virtual void visit_ident(AstIdent* p) = 0;
	virtual void visit_load(AstLoad* p) = 0;
	virtual void visit_indexed_load(AstIndexedLoad* p) = 0;
	virtual void visit_mk_scope(AstMkScope* p) = 0;
	virtual void visit_rm_scope(AstRmScope* p) = 0;
	virtual void visit_assign(AstAssign* p) = 0;
	virtual void visit_indexed_assign(AstIndexedAssign* p) = 0;
	virtual void visit_binop(AstBinop* p) = 0;
	virtual void visit_if(AstIf* p) = 0;
	virtual void visit_if_chain(AstIfChain* p) = 0;
	virtual void visit_while(AstWhile* p) = 0;
	virtual void visit_do_while(AstDoWhile* p) = 0;
	virtual void visit_builtin_typename(AstBuiltinTypename* p) = 0;
	virtual void visit_var_decl_simple(AstVarDeclSimple* p) = 0;
	virtual void visit_var_decl_array(AstVarDeclArray* p) = 0;
	virtual void visit_var_decl_with_init(AstVarDeclWithInit* p) = 0;

};

#endif		// visitor_class_hpp
