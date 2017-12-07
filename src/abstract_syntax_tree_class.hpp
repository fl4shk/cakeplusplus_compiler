#ifndef abstract_syntax_tree_class_hpp
#define abstract_syntax_tree_class_hpp

#include "ast_node_classes.hpp"


class AbstractSyntaxTree
{
protected:		// variables
	AstNode __nodes;
	Tree __tree;

public:		// functions
	AbstractSyntaxTree();
	virtual ~AbstractSyntaxTree();

	AstNode* gen_op_constant(int some_num);
	AstNode* gen_op_ident(char* a);
	AstNode* gen_op_var_decl(char* some_type_name, char* some_ident);
	AstNode* gen_op_mkscope();
	AstNode* gen_op_rmscope();
	//AstNode* gen_op_block(AstNode* start_node, 
	//	AstNode* inner_node, AstNode* end_node);
	AstNode* gen_op_assign(char* some_ident, AstNode* some_expr);
	AstNode* gen_op_binary(char* some_op, AstNode* a, 
		AstNode* b);
	void prepend(AstNode* to_prepend);

	void print() const;

protected:		// functions
	inline AstNode* mknode(const AstNode& to_append)
	{
		AstNode* p = new AstNode();
		*p = to_append;
		p->next = &__nodes;
		(p->prev = __nodes.prev)->next = p;
		return(__nodes.prev = p);
	}
	inline void rmnode(AstNode* p)
	{
		__delink_node(p);
		delete p;
	}

	inline void __delink_node(AstNode* p)
	{
		(p->prev)->next = p->next;
		(p->next)->prev = p->prev;
	}




	inline void __relink_node(AstNode* p, AstNode* to_link_after)
	{
		AstNode* old_next = to_link_after->next;

		to_link_after->next = p;
		p->prev = to_link_after;
		p->next = old_next;
		old_next->prev = p;
	}

	//inline Tree* mktree(AstNode* s_start)
	//{
	//	Tree* p = new Tree();
	//	p->start = s_start;
	//	p->next = &__tree;
	//	(p->prev = __tree.prev)->next = p;
	//	return(__tree.prev = p);
	//}

	inline void rmtree(Tree* p)
	{
		__delink_tree(p);
		delete p;
	}
	inline void __delink_tree(Tree* p)
	{
		(p->prev)->next = p->next;
		(p->next)->prev = p->prev;
	}
	inline void __relink_tree(Tree* p, Tree* to_link_after)
	{
		Tree* old_next = to_link_after->next;

		to_link_after->next = p;
		p->prev = to_link_after;
		p->next = old_next;
		old_next->prev = p;
	}

	//inline AstNode* binop(IrCodeOp some_op, AstNode* a, 
	//	AstNode* b)
	//{
	//	AstNode p;
	//	p.op = some_op;
	//	p.args[0] = (AstNode*)a;
	//	p.args[1] = (AstNode*)b;
	//	return mknode(p);
	//}
};

extern AbstractSyntaxTree ast;


#endif		// abstract_syntax_tree_class_hpp
