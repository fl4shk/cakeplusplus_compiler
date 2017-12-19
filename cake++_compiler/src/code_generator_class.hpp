#ifndef code_generator_class_hpp
#define code_generator_class_hpp


#include "abstract_syntax_tree_classes.hpp"

class CodeGenerator
{
protected:		// variables
	// Table of functions
	FunctionTable __func_tbl;

	// Current function
	Function* __curr_func;

public:		// functions
	CodeGenerator();
	virtual ~CodeGenerator();

	void generate(AstNode* prog_node);


protected:		// functions
	void __visit_child(AstNode* p);
	void visit_all_children(AstNode* p);
	void visit_prog(AstNode* p);
	void __visit_func_decl_statements(AstNode* p);
	//void visit_cls_decl(AstNode* p);
	void visit_func_arg_decl(AstNode* p);
	void visit_func_arg_expr(AstNode* p);
	void visit_stmt(AstNode* p);
	void visit_ident_decl(AstNode* p);
	void visit_expr(AstNode* p);


	void visit_subop_bin(AstNode* p);
	void visit_subop_un(AstNode* p);

	inline auto& curr_func()
	{
		return *__curr_func;
	}
	inline auto& sym_tbl()
	{
		return curr_func().sym_tbl();
	}

	inline void err(const std::string& msg)
	{
		printerr("Error:  ", msg, "\n");
		exit(1);
	}
};


#endif		// code_generator_class_hpp
