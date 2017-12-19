#ifndef abstract_syntax_tree_classes_hpp
#define abstract_syntax_tree_classes_hpp

#include "misc_includes.hpp"

//#include "symbol_table_classes.hpp"
#include "ident_table_class.hpp"


#include "symbol_table_classes.hpp"

enum class AstOp
{
	Prog,
	FuncDecl,
	//ClsDecl,
	FuncArgDecl,
	FuncArgExpr,
	Stmt,
	IdentDecl,
	Expr,

};

enum class AstFuncArgDeclOp
{
	Scalar,
	Arr,
	//Cls,
	//ClsArr,

};

enum class AstStmtOp
{
	List,
	VarDecl,
	Assignment,
	If,
	IfChain,
	ListStmtsElse,
	While,
	DoWhile,
	ReturnExpr,
	ReturnNothing,
	Expr,
};

enum class AstIdentDeclOp
{
	Scalar,
	Arr,

	//Cls,
	//ClsArr,

	//ClsMember
	//ClsMemberScalar,
	//ClsMemberArr,
	//ClsMemberCls,
	//ClsMemberClsarr,
	//ClsMemberFunc,
};

enum class AstExprOp
{
	Constant,
	Binop,
	Unop,
	FuncCall,
	IdentScalar,
	IdentArrElem,

	//IdentClsMemberScalar,
	//IdentClsMemberArrElem,
	//IdentClsMemberCls,
	//IdentClsMemberFuncCall,

	Len,
	Sizeof,


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

// Node of the abstract syntax tree
class AstNode
{
public:		// variables
	//size_t line_num, position_in_line;

	AstOp op;
	BuiltinTypename builtin_typename = BuiltinTypename::Blank;

	s64 num;

	Ident ident = nullptr;


	union
	{
		AstFuncArgDeclOp func_arg_decl_op;

		AstStmtOp stmt_op;

		AstIdentDeclOp ident_decl_op;

		AstExprOp expr_op;
	};

	// Making this a union saves space
	union
	{
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

	void output_as_json(Json::Value& output_root) const;

protected:		// functions
	void __output_func_arg_decl_as_json(Json::Value& output_root) const;
	void __output_stmt_as_json(Json::Value& output_root) const;
	void __output_ident_decl_as_json(Json::Value& output_root) const;
	void __output_expr_as_json(Json::Value& output_root) const;
	void __output_expr_constant_as_json(Json::Value& output_root) const;
	void __output_expr_bin_op_as_json(Json::Value& output_root) const;
	void __output_expr_un_op_as_json(Json::Value& output_root) const;

};

extern AstNode* mk_ast_node();

inline auto mk_ast_node(AstOp s_op)
{
	auto ret = mk_ast_node();
	ret->op = s_op;
	return ret;
}

inline auto mk_ast_func_arg_decl(AstFuncArgDeclOp s_func_arg_decl_op)
{
	auto ret = mk_ast_node(AstOp::FuncArgDecl);
	ret->func_arg_decl_op = s_func_arg_decl_op;
	return ret;
}
inline auto mk_ast_stmt(AstStmtOp s_stmt_op)
{
	auto ret = mk_ast_node(AstOp::Stmt);
	ret->stmt_op = s_stmt_op;
	return ret;
}
inline auto mk_ast_ident_decl(AstIdentDeclOp s_ident_decl_op)
{
	auto ret = mk_ast_node(AstOp::IdentDecl);
	ret->ident_decl_op = s_ident_decl_op;
	return ret;
}
inline auto mk_ast_expr(AstExprOp s_expr_op)
{
	auto ret = mk_ast_node(AstOp::Expr);
	ret->expr_op = s_expr_op;
	return ret;
}

#endif		// abstract_syntax_tree_classes_hpp
