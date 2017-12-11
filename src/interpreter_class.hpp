#ifndef interpreter_class_hpp
#define interpreter_class_hpp

#include "visitor_class.hpp"
#include "abstract_syntax_tree_class.hpp"
#include "symbol_table_class.hpp"

class Interpreter : public Visitor
{
protected:		// variables
	std::string __ident_name;
	//std::vector<int> __expr_values;

public:		// functions
	void interpret();


	void visit_program(AstProgram* p);
	void visit_statements(AstStatements* p);
	void visit_list_statement(AstListStatement* p);
	void visit_constant(AstConstant* p);
	void visit_ident(AstIdent* p);
	void visit_indexed_load(AstIndexedLoad* p);
	void visit_mk_scope(AstMkScope* p);
	void visit_rm_scope(AstRmScope* p);
	void visit_assign(AstAssign* p);
	void visit_indexed_assign(AstIndexedAssign* p);
	void visit_binop(AstBinop* p);
	void visit_if(AstIf* p);
	void visit_if_chain(AstIfChain* p);
	void visit_while(AstWhile* p);
	void visit_do_while(AstDoWhile* p);
	void visit_builtin_typename(AstBuiltinTypename* p);
	void visit_var_decl_simple(AstVarDeclSimple* p);
	void visit_var_decl_array(AstVarDeclArray* p);
	void visit_var_decl_with_init(AstVarDeclWithInit* p);

};

extern std::unique_ptr<Interpreter> interpreter;

#endif		// interpreter_class_hpp
