#ifndef abstract_syntax_tree_classes_hpp
#define abstract_syntax_tree_classes_hpp

#include "misc_includes.hpp"

//#include "symbol_table_classes.hpp"
#include "ident_table_class.hpp"

enum class AstOp
{
	prog,
	func_decl,
	func_call,

	list_func_var_decls,

	func_var_decl_scalar,
	func_var_decl_arr,

	func_arg_expr,


	expr_constant,
	expr_binop,
	expr_unop,
	expr_func_call,
	expr_ident_scalar,
	expr_ident_arr_elem,

	list_stmts,
	stmt_var_decl,

	stmt_assignment,
	stmt_if,
	stmt_if_chain,
	list_stmts_else,
	stmt_while,
	stmt_do_while,

	ident_decl_scalar,
	ident_decl_arr,

};

// Binary operator AST node
enum class AstBinOp
{
	Add,
	Sub,
	Mul,
	UDiv,
	SDiv,
	UMod,
	SMod,

	BitAnd,
	BitOr,
	BitXor,

	BitLsl,
	BitLsr,
	BitAsr,

	LogAnd,
	LogOr,

	CmpEq,
	CmpNe,

	CmpULt,
	CmpUGt,
	CmpULe,
	CmpUGe,

	CmpSLt,
	CmpSGt,
	CmpSLe,
	CmpSGe,
};

// Unary operator AST node
enum class AstUnOp
{
	BitInvert,
	Negate,
	LogNot,
};
enum class BuiltinTypename;

// Node of the abstract syntax tree
class AstNode
{
public:		// variables
	AstOp op;
	BuiltinTypename type;

	// Making this a union saves space
	union
	{
		// String (often an identifier, but not always used)
		std::string* str;

		// Binary operator type
		AstBinOp bin_op;

		// Unary operator type
		AstUnOp un_op;
	};


	// The childrens
	std::vector<AstNode*> children;

public:		// functions
	AstNode();
	AstNode(AstOp s_op, std::vector<AstNode*>&& s_children);
	AstNode(AstNode&& to_move) = default;

	virtual ~AstNode();


	AstNode& operator = (AstNode&& to_move) = default;


	inline void append_child(AstNode* to_append)
	{
		children.push_back(to_append);
	}

};

#endif		// abstract_syntax_tree_classes_hpp
