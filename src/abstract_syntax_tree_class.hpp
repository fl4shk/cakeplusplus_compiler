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
	AstNode* gen_indexed_load(AstNode* some_ident_node, 
		AstNode* some_index);
	AstNode* gen_mkscope();
	AstNode* gen_rmscope();
	AstNode* gen_assign(AstNode* some_ident_node, AstNode* some_expr);
	AstNode* gen_indexed_assign(AstNode* some_ident_node,
		AstNode* some_index, AstNode* some_rhs);
	AstNode* gen_finished_binop(AstNode* some_incomplete_binop, 
		AstNode* a, AstNode* b);

	AstNode* gen_if_statement(AstNode* some_expr, 
		AstNode* some_statement);
	AstNode* gen_if_chain_statement(AstNode* some_expr,
		AstNode* some_statement_if, AstNode* some_statement_else);
	AstNode* gen_while_statement(AstNode* some_expr,
		AstNode* some_statement);
	AstNode* gen_do_while_statement(AstNode* some_statement,
		AstNode* some_expr);

	AstNode* gen_builtin_typename(char* some_typename_node);
	AstNode* gen_var_decl_simple(AstNode* some_typename_node, 
		AstNode* some_ident_node);
	AstNode* gen_var_decl_array(AstNode* some_typename_node, 
		AstNode* some_ident_node, AstNode* some_dim);
	AstNode* gen_var_decl_with_init(AstNode* some_typename_node,
		AstNode* some_ident_node, AstNode* some_expr);

	inline void print() const
	{
		printout(__program);
	}

	void print_json() const;

	gen_getter_by_val(program);

	inline AstNode* make_initial_binop_node()
	{
		return mknode<AstBinop>();
	}


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
