#ifndef interpreter_class_hpp
#define interpreter_class_hpp

#include "visitor_class.hpp"
#include "abstract_syntax_tree_class.hpp"
#include "symbol_table_class.hpp"
#include <stack>

class Interpreter : public Visitor
{
protected:		// variables
	std::vector<std::string*> __str_vec;
	std::vector<int> __num_vec;

public:		// functions
	void interpret();


	void visit_program(AstProgram* p);
	void visit_statements(AstStatements* p);
	void visit_list_statement(AstListStatement* p);
	void visit_constant(AstConstant* p);
	void visit_ident(AstIdent* p);
	void visit_load(AstLoad* p);
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

protected:		// functions
	inline void push_num(int to_push)
	{
		__num_vec.push_back(to_push);
	}
	inline auto pop_num()
	{
		const auto num = __num_vec.back();
		__num_vec.pop_back();
		return num;
	}
	inline void push_str(std::string* to_push)
	{
		__str_vec.push_back(to_push);
	}
	inline auto pop_str()
	{
		auto str = __str_vec.back();
		__str_vec.pop_back();
		return str;
	}

};

extern Interpreter interpreter;

#endif		// interpreter_class_hpp
