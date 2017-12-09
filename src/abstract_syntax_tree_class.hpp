#ifndef abstract_syntax_tree_class_hpp
#define abstract_syntax_tree_class_hpp

#include "ast_node_classes.hpp"


class AbstractSyntaxTree
{
protected:		// variables
	//AstNode __tree;
	AstNode* __program = nullptr;
	std::vector<std::unique_ptr<AstNode>> __nodes;

public:		// functions
	AbstractSyntaxTree();
	virtual ~AbstractSyntaxTree();

	AstNode* gen_program(AstNode* some_statements);
	AstNode* gen_statements(AstNode* some_mkscope, 
		AstNode* some_list_statement, AstNode* some_rmscope);
	AstNode* gen_list_statement();
	AstNode* gen_statement();
	AstNode* gen_constant(int some_num);
	AstNode* gen_ident(const char* some_ident);
	AstNode* gen_mkscope();
	AstNode* gen_rmscope();
	AstNode* gen_assign(const char* some_ident, AstNode* some_expr);
	AstNode* gen_binop(const char* some_op, AstNode* a, AstNode* b);

	AstNode* gen_if_statement(AstNode* some_expr, 
		AstNode* some_statement);
	AstNode* gen_if_chain_statement(AstNode* some_expr,
		AstNode* some_statement_if, AstNode* some_statement_else);
	AstNode* gen_while_statement(AstNode* some_expr,
		AstNode* some_statement);
	AstNode* gen_do_while_statement(AstNode* some_statement,
		AstNode* some_expr);

	AstNode* gen_builtin_typename(const char* some_type_name);
	AstNode* gen_var_decl_simple(const char* some_type_name, 
		const char* some_ident);
	AstNode* gen_var_decl_array(const char* some_type_name, 
		const char* some_ident, int some_dim);

	inline void print() const
	{
		printout(__program);
	}

	void print_json() const;

protected:		// functions
	template<typename NodeType>
	inline AstNode* mknode()
	{
		std::unique_ptr<AstNode> p;
		p.reset(new NodeType());
		__nodes.push_back(std::move(p));
		return __nodes.back().get();
	}

};

extern AbstractSyntaxTree ast;


#endif		// abstract_syntax_tree_class_hpp
