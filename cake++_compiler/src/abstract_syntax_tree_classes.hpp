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

	func_arg_decl_scalar,
	func_arg_decl_arr,
	func_arg_expr,


	list_stmts,


	stmt_var_decl,
	stmt_assignment,
	stmt_if,
	stmt_if_chain,
	list_stmts_else,
	stmt_while,
	stmt_do_while,
	stmt_return_expr,
	stmt_return_nothing,


	ident_decl_scalar,
	ident_decl_arr,


	expr_constant,
	expr_binop,
	expr_unop,
	expr_ident_scalar,
	expr_ident_arr_elem,

	expr_len,
	expr_sizeof,


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
	BuiltinTypename builtin_typename;

	s64 num;

	Ident ident = nullptr;

	// Making this a union saves space
	union
	{
		// Binary operator type
		AstBinOp bin_op;

		// Unary operator type
		AstUnOp un_op;
	};


	// The childrens
	std::deque<AstNode*> children;

public:		// functions
	AstNode();
	AstNode(AstOp s_op, std::deque<AstNode*>&& s_children);
	AstNode(AstNode&& to_move) = default;

	virtual ~AstNode();


	AstNode& operator = (AstNode&& to_move) = default;


	inline void prepend_child(AstNode* to_prepend)
	{
		children.push_front(to_prepend);
	}
	inline void append_child(AstNode* to_append)
	{
		children.push_back(to_append);
	}

	void output_as_json(Json::Value& output_root);

};

extern AstNode* mk_ast_node();

inline auto mk_ast_node(AstOp s_op)
{
	auto ret = mk_ast_node();
	ret->op = s_op;
	return ret;
}

#endif		// abstract_syntax_tree_classes_hpp
