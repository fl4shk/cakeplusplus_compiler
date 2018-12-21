#ifndef src_ast_visitor_class_hpp
#define src_ast_visitor_class_hpp

// src/ast_visitor_class.hpp

#include "ast_node_classes.hpp"

namespace cake_plus_plus
{

class AstVisitor
{
private:		// variables

public:		// functions
	void visit_program(AstNodeBase* program)
	{
	}
	void visit_list_functions(AstNodeBase* list_functions)
	{
	}
	void visit_function(AstNodeBase* function)
	{
	}
	void visit_list_function_args(AstNodeBase* list_function_args)
	{
	}
	void visit_list_statements(AstNodeBase* list_statements)
	{
	}
};

} // end namespace cake_plus_plus


#endif		// src_ast_visitor_class_hpp
