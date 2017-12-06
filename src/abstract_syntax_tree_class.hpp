#ifndef abstract_syntax_tree_class_hpp
#define abstract_syntax_tree_class_hpp

#include "abstract_syntax_tree_node_classes.hpp"


class AbstractSyntaxTree
{
protected:		// variables
	

public:		// functions
	void* gen_op_mkscope();
	void* gen_op_rmscope();
	void* gen_op_var_decl(char* some_type_name, char* some_ident);
	void* gen_op_assign(char* some_ident, void* some_expr);
	void* gen_op_constant(int some_num);
	void* gen_op_binary(char* some_op, void* a, void* b);

	void print() const;

};

extern AbstractSyntaxTree ast;


#endif		// abstract_syntax_tree_class_hpp
