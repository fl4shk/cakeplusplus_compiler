#ifndef src_ast_node_classes_hpp
#define src_ast_node_classes_hpp

// src/ast_node_classes.hpp

#include "misc_includes.hpp"
#include "alloc_stuff.hpp"

namespace cake_plus_plus
{

class AstVisitor;


class AstNodeBase
{
public:		// functions
	virtual ~AstNodeBase();

	virtual void accept(AstVisitor* visitor) = 0;

};

class AstNodeProgram : public AstNodeBase
{
public:		// variables
	AstNodeBase* list_functions = nullptr;

public:		// functions
	void accept(AstVisitor* visitor);

};

class AstNodeListFunctions : public AstNodeBase
{
public:		// variables
	AstNodeBase* function = nullptr;
	AstNodeBase* list_functions = nullptr;

public:		// functions
	void accept(AstVisitor* visitor);

};

class AstNodeFunction : public AstNodeBase
{
public:		// variables
	PtrConstStr type = nullptr, ident = nullptr;
	AstNodeBase* list_function_args = nullptr;
	AstNodeBase* list_statements = nullptr;

public:		// functions
	void accept(AstVisitor* visitor);
};

class AstNodeListFunctionArgs : public AstNodeBase
{
public:		// variables
	AstNodeBase* function_arg = nullptr;
	AstNodeBase* list_function_args = nullptr;

public:		// functions
	void accept(AstVisitor* visitor);
};

} // end namespace cake_plus_plus


#endif		// src_ast_node_classes_hpp
