#include "abstract_syntax_tree_classes.hpp"
#include "symbol_table_classes.hpp"

class JsonAstOpStuff
{
public:		// static variables
	static const std::map<AstOp, std::string> json_ast_op_stuff;
	static const std::map<AstFuncArgDeclOp, std::string>
		json_ast_func_arg_decl_op_stuff;
	static const std::map<AstStmtOp, std::string> json_ast_stmt_op_stuff;
	static const std::map<AstIdentDeclOp, std::string>
		json_ast_ident_decl_op_stuff;
	static const std::map<AstExprOp, std::string> json_ast_expr_op_stuff;
	static const std::map<AstBinOp, std::string> json_ast_binop_stuff;
	static const std::map<AstUnOp, std::string> json_ast_unop_stuff;
};

const std::map<AstOp, std::string> JsonAstOpStuff::json_ast_op_stuff
({
	std::pair(AstOp::Prog, "Prog"),
	std::pair(AstOp::FuncDecl, "FuncDecl"),
	//std::pair(AstOp::ClsDecl, "ClsDecl"),
	std::pair(AstOp::FuncArgDecl, "FuncArgDecl"),
	std::pair(AstOp::FuncArgExpr, "FuncArgExpr"),
	std::pair(AstOp::Stmt, "Stmt"),
	std::pair(AstOp::IdentDecl, "IdentDecl"),
	std::pair(AstOp::Expr, "Expr"),
});

const std::map<AstFuncArgDeclOp, std::string>
	JsonAstOpStuff::json_ast_func_arg_decl_op_stuff
({
	std::pair(AstFuncArgDeclOp::Scalar, "Scalar"),
	std::pair(AstFuncArgDeclOp::Arr, "Arr"),
	//std::pair(AstFuncArgDeclOp::Cls, "Cls"),
	////std::pair(AstFuncArgDeclOp::ClsArr, "ClsArr"),
});
const std::map<AstStmtOp, std::string> 
	JsonAstOpStuff::json_ast_stmt_op_stuff
({
	std::pair(AstStmtOp::List, "List"),
	std::pair(AstStmtOp::VarDecl, "VarDecl"),
	std::pair(AstStmtOp::Assignment, "Assignment"),
	std::pair(AstStmtOp::If, "If"),
	std::pair(AstStmtOp::IfChain, "IfChain"),
	std::pair(AstStmtOp::ListStmtsElse, "ListStmtsElse"),
	std::pair(AstStmtOp::While, "While"),
	std::pair(AstStmtOp::DoWhile, "DoWhile"),
	std::pair(AstStmtOp::ReturnExpr, "ReturnExpr"),
	std::pair(AstStmtOp::ReturnNothing, "ReturnNothing"),
	std::pair(AstStmtOp::Expr, "Expr"),
});

const std::map<AstIdentDeclOp, std::string>
	JsonAstOpStuff::json_ast_ident_decl_op_stuff
({
	std::pair(AstIdentDeclOp::Scalar, "Scalar"),
	std::pair(AstIdentDeclOp::Arr, "Arr"),

	//std::pair(AstIdentDeclOp::Cls, "Cls"),
	//std::pair(AstIdentDeclOp::ClsArr, "ClsArr"),

	//std::pair(AstIdentDeclOp::ClsMember "ClsMember"),
	//std::pair(AstIdentDeclOp::ClsMemberScalar, "ClsMemberScalar"),
	//std::pair(AstIdentDeclOp::ClsMemberArr, "ClsMemberArr"),
	//std::pair(AstIdentDeclOp::ClsMemberCls, "ClsMemberCls"),
	//std::pair(AstIdentDeclOp::ClsMemberClsarr, "ClsMemberClsarr"),
	//std::pair(AstIdentDeclOp::ClsMemberFunc, "ClsMemberFunc"),
});
const std::map<AstExprOp, std::string>
	JsonAstOpStuff::json_ast_expr_op_stuff
({
	std::pair(AstExprOp::Constant, "Constant"),
	std::pair(AstExprOp::Binop, "Binop"),
	std::pair(AstExprOp::Unop, "Unop"),
	std::pair(AstExprOp::FuncCall, "FuncCall"),
	std::pair(AstExprOp::IdentScalar, "IdentScalar"),
	std::pair(AstExprOp::IdentArrElem, "IdentArrElem"),

	//std::pair(AstExprOp::IdentClsMemberScalar, "IdentClsMemberScalar"),
	//std::pair(AstExprOp::IdentClsMemberArrElem, "IdentClsMemberArrElem"),
	//std::pair(AstExprOp::IdentClsMemberCls, "IdentClsMemberCls"),
	//std::pair(AstExprOp::IdentClsMemberFuncCall, "IdentClsMemberFuncCall"),

	std::pair(AstExprOp::Len, "Len"),
	std::pair(AstExprOp::Sizeof, "Sizeof"),
});
const std::map<AstBinOp, std::string> JsonAstOpStuff::json_ast_binop_stuff
({
	std::pair(AstBinOp::Add, "Add"),
	std::pair(AstBinOp::Sub, "Sub"),
	std::pair(AstBinOp::Mul, "Mul"),
	std::pair(AstBinOp::UDiv, "UDiv"),
	std::pair(AstBinOp::SDiv, "SDiv"),
	std::pair(AstBinOp::UMod, "UMod"),
	std::pair(AstBinOp::SMod, "SMod"),

	std::pair(AstBinOp::BitAnd, "BitAnd"),
	std::pair(AstBinOp::BitOr, "BitOr"),
	std::pair(AstBinOp::BitXor, "BitXor"),

	std::pair(AstBinOp::BitLsl, "BitLsl"),
	std::pair(AstBinOp::BitLsr, "BitLsr"),
	std::pair(AstBinOp::BitAsr, "BitAsr"),

	std::pair(AstBinOp::LogAnd, "LogAnd"),
	std::pair(AstBinOp::LogOr, "LogOr"),

	std::pair(AstBinOp::CmpEq, "CmpEq"),
	std::pair(AstBinOp::CmpNe, "CmpNe"),

	std::pair(AstBinOp::CmpULt, "CmpULt"),
	std::pair(AstBinOp::CmpUGt, "CmpUGt"),
	std::pair(AstBinOp::CmpULe, "CmpULe"),
	std::pair(AstBinOp::CmpUGe, "CmpUGe"),

	std::pair(AstBinOp::CmpSLt, "CmpSLt"),
	std::pair(AstBinOp::CmpSGt, "CmpSGt"),
	std::pair(AstBinOp::CmpSLe, "CmpSLe"),
	std::pair(AstBinOp::CmpSGe, "CmpSGe"),
});
const std::map<AstUnOp, std::string> JsonAstOpStuff::json_ast_unop_stuff
({
	std::pair(AstUnOp::BitInvert, "BitInvert"),
	std::pair(AstUnOp::Negate, "Negate"),
	std::pair(AstUnOp::LogNot, "LogNot"),
});

AstNode::AstNode()
{
}

AstNode::AstNode(AstOp s_op, std::deque<AstNode*>&& s_children)
	: op(s_op), children(std::move(s_children))
{
}
AstNode::~AstNode()
{
}


void AstNode::output_as_json(Json::Value& output_root)
{
	//if (json_ast_op_stuff.count(op) == 0)
	//{
	//	printerr("AstNode::output_as_json():  op Eek!\n");
	//	exit(1);
	//}

	//output_root["__op"] = json_ast_op_stuff.at(op);
	//if (ident != nullptr)
	//{
	//	output_root["_ident"] = *ident;
	//}

	//switch (op)
	//{
	//	case AstOp::prog:
	//		break;
	//	case AstOp::func_decl:
	//		break;
	//	case AstOp::func_call:
	//		break;

	//	case AstOp::func_arg_decl_scalar:
	//		break;
	//	case AstOp::func_arg_decl_arr:
	//		break;
	//	case AstOp::func_arg_expr:
	//		break;


	//	case AstOp::list_stmts:
	//		break;


	//	case AstOp::stmt_var_decl:
	//		switch (builtin_typename)
	//		{
	//			case BuiltinTypename::U64:
	//				output_root["builtin_typename"] = "u64";
	//				break;
	//			case BuiltinTypename::S64:
	//				output_root["builtin_typename"] = "s64";
	//				break;
	//			case BuiltinTypename::U32:
	//				output_root["builtin_typename"] = "u32";
	//				break;
	//			case BuiltinTypename::S32:
	//				output_root["builtin_typename"] = "s32";
	//				break;
	//			case BuiltinTypename::U16:
	//				output_root["builtin_typename"] = "u16";
	//				break;
	//			case BuiltinTypename::S16:
	//				output_root["builtin_typename"] = "s16";
	//				break;
	//			case BuiltinTypename::U8:
	//				output_root["builtin_typename"] = "u8";
	//				break;
	//			case BuiltinTypename::S8:
	//				output_root["builtin_typename"] = "s8";
	//				break;
	//			default:
	//				printerr("AstNode::output_as_json():  ",
	//					"builtin_typename Eek!\n");
	//				exit(1);
	//				break;
	//		}
	//		break;
	//	case AstOp::stmt_assignment:
	//		break;
	//	case AstOp::stmt_if:
	//		break;
	//	case AstOp::stmt_if_chain:
	//		break;
	//	case AstOp::list_stmts_else:
	//		break;
	//	case AstOp::stmt_while:
	//		break;
	//	case AstOp::stmt_do_while:
	//		break;
	//	case AstOp::stmt_return_expr:
	//		break;
	//	case AstOp::stmt_return_nothing:
	//		break;


	//	case AstOp::ident_decl_scalar:
	//		break;
	//	case AstOp::ident_decl_arr:
	//		break;


	//	case AstOp::expr_constant:
	//		output_root["num"] = num;
	//		break;

	//	case AstOp::expr_binop:
	//		if (json_ast_binop_stuff.count(bin_op) == 0)
	//		{
	//			printerr("AstNode::output_as_json():  bin_op Eek!\n");
	//			exit(1);
	//		}
	//		output_root["binop"] = json_ast_binop_stuff.at(bin_op);
	//		break;

	//	case AstOp::expr_unop:
	//		if (json_ast_unop_stuff.count(un_op) == 0)
	//		{
	//			printerr("AstNode::output_as_json():  un_op Eek!\n");
	//			exit(1);
	//		}
	//		output_root["unop"] = json_ast_unop_stuff.at(un_op);
	//		break;

	//	case AstOp::expr_ident_scalar:
	//		break;
	//	case AstOp::expr_ident_arr_elem:
	//		break;

	//	case AstOp::expr_len:
	//		break;
	//	case AstOp::expr_sizeof:
	//		break;

	//	default:
	//		printerr("AstNode::output_as_json():  Bug!  Eek!\n");
	//		exit(1);
	//		break;
	//}

	//for (size_t i=0; i<children.size(); ++i)
	//{
	//	const Json::ArrayIndex index_i = i;
	//	children.at(i)->output_as_json(output_root["children"][index_i]);
	//}


}
