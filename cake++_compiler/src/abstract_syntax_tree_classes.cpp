#include "abstract_syntax_tree_classes.hpp"
#include "symbol_table_classes.hpp"

const std::map<AstOp, std::string> json_ast_op_stuff
({
	std::pair(AstOp::prog, "prog"),
	std::pair(AstOp::func_decl, "func_decl"),
	std::pair(AstOp::func_call, "func_call"),

	std::pair(AstOp::func_arg_decl_scalar,
		"func_arg_decl_scalar"),
	std::pair(AstOp::func_arg_decl_arr, "func_arg_decl_arr"),
	std::pair(AstOp::func_arg_expr, "func_arg_expr"),


	std::pair(AstOp::list_stmts, "list_stmts"),


	std::pair(AstOp::stmt_var_decl, "stmt_var_decl"),
	std::pair(AstOp::stmt_assignment, "stmt_assignment"),
	std::pair(AstOp::stmt_if, "stmt_if"),
	std::pair(AstOp::stmt_if_chain, "stmt_if_chain"),
	std::pair(AstOp::list_stmts_else, "list_stmts_else"),
	std::pair(AstOp::stmt_while, "stmt_while"),
	std::pair(AstOp::stmt_do_while, "stmt_do_while"),
	std::pair(AstOp::stmt_return_expr, "stmt_return_expr"),
	std::pair(AstOp::stmt_return_nothing,
		"stmt_return_nothing"),


	std::pair(AstOp::ident_decl_scalar, "ident_decl_scalar"),
	std::pair(AstOp::ident_decl_arr, "ident_decl_arr"),


	std::pair(AstOp::expr_constant, "expr_constant"),
	std::pair(AstOp::expr_binop, "expr_binop"),
	std::pair(AstOp::expr_unop, "expr_unop"),
	std::pair(AstOp::expr_ident_scalar, "expr_ident_scalar"),
	std::pair(AstOp::expr_ident_arr_elem,
		"expr_ident_arr_elem"),

	std::pair(AstOp::expr_len, "expr_len"),
	std::pair(AstOp::expr_sizeof, "expr_sizeof"),
});
const std::map<AstBinOp, std::string> json_ast_binop_stuff
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
const std::map<AstUnOp, std::string> json_ast_unop_stuff
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
	if (json_ast_op_stuff.count(op) == 0)
	{
		printerr("AstNode::output_as_json():  op Eek!\n");
		exit(1);
	}

	output_root["_op"] = json_ast_op_stuff.at(op);
	if (ident != nullptr)
	{
		output_root["_ident"] = *ident;
	}

	switch (op)
	{
		case AstOp::prog:
			break;
		case AstOp::func_decl:
			break;
		case AstOp::func_call:
			break;

		case AstOp::func_arg_decl_scalar:
			break;
		case AstOp::func_arg_decl_arr:
			break;
		case AstOp::func_arg_expr:
			break;


		case AstOp::list_stmts:
			break;


		case AstOp::stmt_var_decl:
			switch (builtin_typename)
			{
				case BuiltinTypename::U64:
					output_root["builtin_typename"] = "u64";
					break;
				case BuiltinTypename::S64:
					output_root["builtin_typename"] = "s64";
					break;
				case BuiltinTypename::U32:
					output_root["builtin_typename"] = "u32";
					break;
				case BuiltinTypename::S32:
					output_root["builtin_typename"] = "s32";
					break;
				case BuiltinTypename::U16:
					output_root["builtin_typename"] = "u16";
					break;
				case BuiltinTypename::S16:
					output_root["builtin_typename"] = "s16";
					break;
				case BuiltinTypename::U8:
					output_root["builtin_typename"] = "u8";
					break;
				case BuiltinTypename::S8:
					output_root["builtin_typename"] = "s8";
					break;
				default:
					printerr("AstNode::output_as_json():  ",
						"builtin_typename Eek!\n");
					exit(1);
					break;
			}
			break;
		case AstOp::stmt_assignment:
			break;
		case AstOp::stmt_if:
			break;
		case AstOp::stmt_if_chain:
			break;
		case AstOp::list_stmts_else:
			break;
		case AstOp::stmt_while:
			break;
		case AstOp::stmt_do_while:
			break;
		case AstOp::stmt_return_expr:
			break;
		case AstOp::stmt_return_nothing:
			break;


		case AstOp::ident_decl_scalar:
			break;
		case AstOp::ident_decl_arr:
			break;


		case AstOp::expr_constant:
			output_root["num"] = num;
			break;

		case AstOp::expr_binop:
			if (json_ast_binop_stuff.count(bin_op) == 0)
			{
				printerr("AstNode::output_as_json():  bin_op Eek!\n");
				exit(1);
			}
			output_root["binop"] = json_ast_binop_stuff.at(bin_op);
			break;

		case AstOp::expr_unop:
			if (json_ast_unop_stuff.count(un_op) == 0)
			{
				printerr("AstNode::output_as_json():  un_op Eek!\n");
				exit(1);
			}
			output_root["unop"] = json_ast_unop_stuff.at(un_op);
			break;

		case AstOp::expr_ident_scalar:
			break;
		case AstOp::expr_ident_arr_elem:
			break;

		case AstOp::expr_len:
			break;
		case AstOp::expr_sizeof:
			break;

		default:
			printerr("AstNode::output_as_json():  Bug!  Eek!\n");
			exit(1);
			break;
	}

	for (size_t i=0; i<children.size(); ++i)
	{
		const Json::ArrayIndex index_i = i;
		children.at(i)->output_as_json(output_root["children"][index_i]);
	}


}
