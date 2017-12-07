#ifndef abstract_syntax_tree_class_hpp
#define abstract_syntax_tree_class_hpp

#include "abstract_syntax_tree_node_classes.hpp"


class AbstractSyntaxTree
{
public:		// classes
	// Circular linked list of "subtrees".
	class Tree
	{
	public:		// variables
		AstNodeBase* start;
		Tree * next, * prev;
	};

protected:		// variables
	AstNodeBase __nodes;
	Tree __tree;

public:		// functions
	AbstractSyntaxTree();
	virtual ~AbstractSyntaxTree();

	AstNodeBase* gen_op_mkscope();
	AstNodeBase* gen_op_rmscope();
	AstNodeBase* gen_op_var_decl(char* some_type_name, char* some_ident);
	AstNodeBase* gen_op_assign(char* some_ident, AstNodeBase* some_expr);
	AstNodeBase* gen_op_constant(int some_num);
	AstNodeBase* gen_op_binary(char* some_op, AstNodeBase* a, 
		AstNodeBase* b);
	AstNodeBase* gen_op_block(AstNodeBase* start_node, 
		AstNodeBase* inner_node, AstNodeBase* end_node);
	AstNodeBase* gen_op_ident(char* a);
	void prepend(AstNodeBase* to_prepend);

	void print() const;

protected:		// functions
	inline AstNodeBase* mknode(const AstNodeBase& to_append)
	{
		AstNodeBase* p = new AstNodeBase();
		*p = to_append;
		p->next = &__nodes;
		(p->prev = __nodes.prev)->next = p;
		return(__nodes.prev = p);
	}
	inline void rmnode(AstNodeBase* p)
	{
		__delink_node(p);
		delete p;
	}

	inline void __delink_node(AstNodeBase* p)
	{
		(p->prev)->next = p->next;
		(p->next)->prev = p->prev;
	}




	inline void __relink_node(AstNodeBase* p, AstNodeBase* to_link_after)
	{
		AstNodeBase* old_next = to_link_after->next;

		to_link_after->next = p;
		p->prev = to_link_after;
		p->next = old_next;
		old_next->prev = p;
	}

	//inline Tree* mktree(AstNodeBase* s_start)
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

	//inline AstNodeBase* binop(IrCodeOp some_op, AstNodeBase* a, 
	//	AstNodeBase* b)
	//{
	//	AstNodeBase p;
	//	p.op = some_op;
	//	p.args[0] = (AstNodeBase*)a;
	//	p.args[1] = (AstNodeBase*)b;
	//	return mknode(p);
	//}
};

extern AbstractSyntaxTree ast;


#endif		// abstract_syntax_tree_class_hpp
