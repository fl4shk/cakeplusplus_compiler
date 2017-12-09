#ifndef abstract_syntax_tree_class_hpp
#define abstract_syntax_tree_class_hpp

#include "ast_node_classes.hpp"


class AbstractSyntaxTree
{
protected:		// variables
	AstNode __tree;
	std::vector<std::unique_ptr<AstNode>> __nodes;

public:		// functions
	AbstractSyntaxTree();
	virtual ~AbstractSyntaxTree();

	AstNode* gen_program(AstNode* some_statements);
	AstNode* gen_statements(AstNode* some_mkscope, 
		AstNode* some_list_statements, AstNode* some_rmscope);
	AstNode* gen_list_statement();
	AstNode* gen_statement();
	AstNode* gen_constant(int some_num);
	AstNode* gen_ident(const char* some_ident);
	//AstNode* gen_var_decl(char* some_type_name, char* some_ident);
	AstNode* gen_mkscope();
	AstNode* gen_rmscope();
	AstNode* gen_assign(const char* some_ident, AstNode* some_expr);
	AstNode* gen_binop(const char* some_op, AstNode* a, AstNode* b);

	void print() const;

protected:		// functions
	AstNode* mknode();
	//inline void rmnode(AstNode* p)
	//{
	//	__delink_node(p);
	//	delete p;
	//}

	//inline void __delink_node(AstNode* p)
	//{
	//	(p->prev)->next = p->next;
	//	(p->next)->prev = p->prev;
	//}




	//inline void __relink_node(AstNode* p, AstNode* to_link_after)
	//{
	//	AstNode* old_next = to_link_after->next;

	//	to_link_after->next = p;
	//	p->prev = to_link_after;
	//	p->next = old_next;
	//	old_next->prev = p;
	//}

};

extern AbstractSyntaxTree ast;


#endif		// abstract_syntax_tree_class_hpp
