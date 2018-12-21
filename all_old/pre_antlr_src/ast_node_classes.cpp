#include "ast_node_classes.hpp"
#include "ast_visitor_class.hpp"

namespace cake_plus_plus
{

AstNodeBase::~AstNodeBase()
{
}
#define VISIT(to_visit) \
	visitor->visit_##to_visit(to_visit);

#define VISIT_IF(to_visit) \
	if (to_visit) \
	{ \
		VISIT(to_visit) \
	}

void AstNodeProgram::accept(AstVisitor* visitor)
{
	//visitor.visit_program(this);
	VISIT_IF(list_functions)
}

void AstNodeListFunctions::accept(AstVisitor* visitor)
{
	VISIT(function)
	VISIT_IF(list_functions)
}

void AstNodeFunction::accept(AstVisitor* visitor)
{
	VISIT_IF(list_function_args)
	VISIT_IF(list_statements)
}

#undef VISIT
#undef VISIT_IF

} // end namespace cake_plus_plus
