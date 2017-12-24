#include "code_generator_class.hpp"
#include "frontend_class.hpp"


CodeGenerator::CodeGenerator(Frontend* s_frontend)
	: __frontend(s_frontend)
{
}
CodeGenerator::~CodeGenerator()
{
}

IrExpr* CodeGenerator::mk_expr_constant(IrMachineMode s_mm, s64 s_simm)
{
	auto ret = mk_ir_expr(IrExOp::Constant, s_mm);

	ret->simm = s_simm;

	return ret;
}
IrExpr* CodeGenerator::mk_expr_binop(IrMachineMode s_mm, 
	IrBinop s_binop, IrExpr* a, IrExpr* b)
{
	auto ret = mk_ir_expr(IrExOp::Binop, s_mm);

	ret->binop = s_binop;

	ret->append_arg(a);
	ret->append_arg(b);

	return ret;
}
IrExpr* CodeGenerator::mk_expr_unop(IrMachineMode s_mm, IrUnop s_unop, 
	IrExpr* a)
{
	auto ret = mk_ir_expr(IrExOp::Unop, s_mm);

	ret->unop = s_unop;

	ret->append_arg(a);
	return ret;
}
IrExpr* CodeGenerator::mk_expr_ref_sym(Symbol* s_sym)
{
	auto ret = mk_ir_expr(IrExOp::RefSym, IrMachineMode::Pointer);

	ret->sym = s_sym;

	return ret;
}
IrExpr* CodeGenerator::mk_expr_ref_func(Function* s_func)
{
	auto ret = mk_ir_expr(IrExOp::RefFunc, IrMachineMode::Pointer);

	ret->func = s_func;

	return ret;
}
IrExpr* CodeGenerator::mk_expr_ref_lab(s64 s_lab_num)
{
	auto ret = mk_ir_expr(IrExOp::RefLab, IrMachineMode::Pointer);

	ret->lab_num = s_lab_num;

	return ret;
}
IrExpr* CodeGenerator::mk_expr_len(IrMachineMode s_mm, IrExpr* what)
{
	auto ret = mk_ir_expr(IrExOp::Len, s_mm);

	ret->append_arg(what);

	return ret;
}
IrExpr* CodeGenerator::mk_expr_sizeof(IrMachineMode s_mm, IrExpr* what)
{
	auto ret = mk_ir_expr(IrExOp::Sizeof, s_mm);

	ret->append_arg(what);

	return ret;
}
IrExpr* CodeGenerator::mk_expr_unfinished_call_with_ret
	(IrMachineMode s_mm, IrExpr* where)
{
	auto ret = mk_ir_expr(IrExOp::CallWithRet, s_mm);

	ret->append_arg(where);

	return ret;
}
IrExpr* CodeGenerator::mk_expr_mem(IrExpr* where)
{
	auto ret = mk_ir_expr(IrExOp::Mem, IrMachineMode::Pointer);

	ret->append_arg(where);

	return ret;
}
IrExpr* CodeGenerator::mk_expr_ld(IrMachineMode s_mm, IrExpr* where)
{
	auto ret = mk_ir_expr(IrExOp::Ld, s_mm);

	ret->append_arg(where);

	return ret;
}
IrExpr* CodeGenerator::mk_expr_get_next_pc()
{
	return mk_ir_expr(IrExOp::GetNextPc, IrMachineMode::Pointer);
}
IrExpr* CodeGenerator::mk_expr_if_then_else(IrMachineMode s_mm, 
	IrExpr* cond, IrExpr* what_if, IrExpr* what_else)
{
	auto ret = mk_ir_expr(IrExOp::IfThenElse, s_mm);

	ret->append_arg(cond);
	ret->append_arg(what_if);
	ret->append_arg(what_else);

	return ret;
}
//IrExpr* CodeGenerator::mk_expr_cast(IrMachineMode s_mm, IrExpr* expr)
//{
//	auto ret = mk_ir_expr(IrExOp::Cast, s_mm);
//
//	ret->append_arg(expr);
//
//	return ret;
//}

IrCode* CodeGenerator::mk_code_st(IrMachineMode s_st_mm, IrExpr* where, 
	IrExpr* what)
{
	auto ret = mk_linked_ir_code(IrInOp::St);

	ret->set_st_mm(s_st_mm);
	ret->append_arg(where);
	ret->append_arg(what);

	return ret;
}
IrCode* CodeGenerator::mk_code_return_expr(IrExpr* expr)
{
	auto ret = mk_linked_ir_code(IrInOp::ReturnExpr);

	ret->append_arg(expr);

	return ret;
}
IrCode* CodeGenerator::mk_code_return_nothing()
{
	return mk_linked_ir_code(IrInOp::ReturnNothing);
}
IrCode* CodeGenerator::mk_code_quit(IrExpr* val)
{
	auto ret = mk_linked_ir_code(IrInOp::Quit);

	ret->append_arg(val);

	return ret;
}
IrCode* CodeGenerator::mk_code_jump(IrExpr* where)
{
	auto ret = mk_linked_ir_code(IrInOp::Jump);

	ret->append_arg(where);

	return ret;
}
//IrCode* CodeGenerator::mk_code_unfinished_call(IrExpr* where)
//{
//	auto ret = mk_linked_ir_code(IrInOp::Call);
//
//	ret->append_arg(where);
//
//	return ret;
//}
IrCode* CodeGenerator::mk_code_call(IrExpr* call_expr)
{
	auto ret = mk_linked_ir_code(IrInOp::Call);

	ret->append_arg(call_expr);

	return ret;
}
IrCode* CodeGenerator::mk_code_unfinished_syscall
	(IrSyscallShorthandOp s_syscall_shorthand_op)
{
	auto ret = mk_linked_ir_code(IrInOp::Syscall);
	ret->set_syscall_shorthand_op(s_syscall_shorthand_op);
	return ret;
}
IrCode* CodeGenerator::mk_code_unlinked_label()
{
	auto ret = mk_unlinked_ir_code(IrInOp::Label);

	auto& curr_func = __frontend->curr_func();

	++curr_func.last_label_num();
	curr_func.num_to_label_map()[curr_func.last_label_num()] = ret;
	
	ret->set_lab_num(curr_func.last_label_num());

	//return __frontend->relink_ir_code(ret);
	return ret;
}
IrCode* CodeGenerator::mk_code_linked_label()
{
	return __frontend->relink_ir_code(mk_code_unlinked_label());
}



void CodeGenerator::output_func_ir_code_as_json(Json::Value& output_root,
	Function& curr_func)
{
	//printout("CodeGenerator::osprint_func_ir_code() is not finished!\n");

	//osprintout(os, *curr_func.name(), "\n");
	//osprintout(os, "{\n");

	output_root["_func_name"] = *curr_func.name();
	auto& contents = output_root["contents"];

	{
	Json::ArrayIndex index_i = 0;

	for (auto p=curr_func.ir_code().next;
		p!=&curr_func.ir_code();
		p=p->next)
	{
		auto& node = contents[index_i];
		switch (p->iop())
		{
			// Store
			case IrInOp::St:
				//osprintout(os, "st(", p->st_mm(), ", ");
				node["__iop"] = "st";
				node["_mm"] = sconcat(p->st_mm());
				break;

			// Return from subroutine
			case IrInOp::ReturnExpr:
				//osprintout(os, "return_expr(");
				node["__iop"] = "return_expr";
				break;
			case IrInOp::ReturnNothing:
				//osprintout(os, "return_nothing(");
				node["__iop"] = "return_nothing";
				break;

			// Stop the program
			case IrInOp::Quit:
				//osprintout(os, "quit(");
				node["__iop"] = "quit";
				break;


			case IrInOp::Jump:
				//osprintout(os, "jump(");
				node["__iop"] = "jump";
				break;
			case IrInOp::Call:
				//osprintout(os, "call(");
				node["__iop"] = "call";
				break;

			case IrInOp::Syscall:
				//osprintout(os, "syscall(", p->syscall_shorthand_op());
				node["__iop"] = "syscall";
				node["syscall_shorthand_op"] 
					= sconcat(p->syscall_shorthand_op());
				break;
			case IrInOp::Label:
				//osprintout(os, get_label_name(p), ":  ");
				node["__iop"] = "label";
				node["_name"] = get_label_name(p);
				break;
		}


		for (size_t j=0; j<p->args().size(); ++j)
		{
			auto arg = p->args().at(j);
			const Json::ArrayIndex index_j = j;

			output_ir_expr_as_json(node["args"][index_j], arg);

		}

		++index_i;
	}
	}
}

IrCode* CodeGenerator::mk_linked_ir_code(IrInOp s_iop)
{
	return ::mk_linked_ir_code(__frontend->curr_func(), s_iop);
}

void CodeGenerator::output_ir_expr_as_json(Json::Value& node, 
	IrExpr* p)
{
	node["_mm"] = sconcat(p->mm);

	switch (p->op)
	{
		case IrExOp::Constant:
			//osprintout(os, "const", temp,
			//	strappcom2(p->mm, p->simm));
			node["__op"] = "const";
			node["_immediate"] = sconcat(p->simm);
			break;

		// Binary operator
		case IrExOp::Binop:
			//osprintout(os, "_binop", temp, p->mm);
			node["__op"] = "_binop";

			switch (p->binop)
			{
				case IrBinop::Add:
					//osprintout(os, "add, ");
					node["_binop"] = "add";
					break;
				case IrBinop::Sub:
					//osprintout(os, "sub, ");
					node["_binop"] = "sub";
					break;
				case IrBinop::Mul:
					//osprintout(os, "mul, ");
					node["_binop"] = "mul";
					break;
				case IrBinop::Div:
					//osprintout(os, "div, ");
					node["_binop"] = "div";
					break;
				case IrBinop::Mod:
					//osprintout(os, "mod, ");
					node["_binop"] = "mod";
					break;

				case IrBinop::LogAnd:
					//osprintout(os, "log_and, ");
					node["_binop"] = "log_and";
					break;
				case IrBinop::LogOr:
					//osprintout(os, "log_or, ");
					node["_binop"] = "log_or";
					break;

				case IrBinop::BitAnd:
					//osprintout(os, "bit_and, ");
					node["_binop"] = "bit_and";
					break;
				case IrBinop::BitOr:
					//osprintout(os, "bit_or, ");
					node["_binop"] = "bit_or";
					break;
				case IrBinop::BitXor:
					//osprintout(os, "bit_xor, ");
					node["_binop"] = "bit_xor";
					break;

				case IrBinop::BitShiftLeft:
					//osprintout(os, "bit_shift_left, ");
					node["_binop"] = "bit_shift_left";
					break;
				case IrBinop::BitShiftRight:
					//osprintout(os, "bit_shift_right, ");
					node["_binop"] = "bit_shift_right";
					break;

				//case IrBinop::BitRotateLeft:
				//case IrBinop::BitRotateRight:

				case IrBinop::CmpEq:
					//osprintout(os, "cmp_eq, ");
					node["_binop"] = "cmp_eq";
					break;
				case IrBinop::CmpNe:
					//osprintout(os, "cmp_ne, ");
					node["_binop"] = "cmp_ne";
					break;
				case IrBinop::CmpLt:
					//osprintout(os, "cmp_lt, ");
					node["_binop"] = "cmp_lt";
					break;
				case IrBinop::CmpGt:
					//osprintout(os, "cmp_gt, ");
					node["_binop"] = "cmp_gt";
					break;
				case IrBinop::CmpLe:
					//osprintout(os, "cmp_le, ");
					node["_binop"] = "cmp_le";
					break;
				case IrBinop::CmpGe:
					//osprintout(os, "cmp_ge, ");
					node["_binop"] = "cmp_ge";
					break;

				default:
					printerr("CodeGenerator::output_ir_expr_as_json():  ",
						"Binop Eek!\n");
					exit(1);
					break;
			}
			break;

		// Unary operator
		case IrExOp::Unop:
			//osprintout(os, "unop", temp,
			//	p->mm);
			node["__op"] = "unop";

			switch (p->unop)
			{
				case IrUnop::BitNot:
					//osprintout(os, "bit_not, ");
					node["_unop"] = "bit_not";
					break;
				case IrUnop::Negate:
					//osprintout(os, "negate, ");
					node["_unop"] = "negate";
					break;
				case IrUnop::LogNot:
					//osprintout(os, "log_not, ");
					node["_unop"] = "log_not";
					break;
				default:
					printerr("CodeGenerator::output_ir_expr_as_json():  ",
						"Unop Eek!\n");
					exit(1);
					break;
			}
			break;

		// Symbol reference
		case IrExOp::RefSym:
			//osprintout(os, "ref_sym", temp,
			//	strappcom2(p->mm, *p->sym->name()));
			node["__op"] = "ref_sym";
			node["_name"] = *p->sym->name();
			break;

		// Function reference
		case IrExOp::RefFunc:
			///osprintout(os, "ref_func", temp,
			///	strappcom2(p->mm, *p->func->name()));
			node["__op"] = "ref_func";
			node["_name"] = *p->func->name();
			break;

		// Label reference
		case IrExOp::RefLab:
			//osprintout(os, "ref_lab", temp,
			//	strappcom2(p->mm, get_label_name(p->lab_num)));
			node["__op"] = "ref_lab";
			node["_name"] = get_label_name(p->lab_num);
			break;

		// Length of symbol
		case IrExOp::Len:
			//osprintout(os, "len", temp, p->mm);
			node["__op"] = "len";
			break;

		// Size of symbol
		case IrExOp::Sizeof:
			//osprintout(os, "sizeof", temp, p->mm);
			node["__op"] = "sizeof";
			break;


		// Call with a return value
		case IrExOp::CallWithRet:
			//osprintout(os, "call_with_ret", temp, p->mm);
			node["__op"] = "call_with_ret";
			break;


		// Memory address (example of use:  grabs address from symbol, 
		case IrExOp::Mem:
			//osprintout(os, "mem", temp, p->mm);
			node["__op"] = "mem";
			break;

		// Load
		case IrExOp::Ld:
			//osprintout(os, "ld", temp, p->mm);
			node["__op"] = "ld";
			break;

		// Sometimes used for the "Else" portion of IfThenElse
		case IrExOp::GetNextPc:
			//osprintout(os, "get_next_pc", temp, p->mm);
			node["__op"] = "get_next_pc";
			break;


		// Control flow
		case IrExOp::IfThenElse:
			//osprintout(os, "if_then_else", temp, p->mm);
			node["__op"] = "if_then_else";
			break;

		//case IrExOp::Cast
		//	node["__op"] = "cast";
		//	break;

		default:
			printerr("CodeGenerator::output_ir_expr_as_json():  Eek!\n");
			exit(1);
			break;
	}

	//if (p->args.size() > 0)
	//{
	//	osprintout(os, ",\n");
	//}
	for (size_t i=0; i<p->args.size(); ++i)
	{
		auto arg = p->args.at(i);
		const Json::ArrayIndex index_i = i;

		output_ir_expr_as_json(node["args"][index_i], arg);
	}


	//osprintout(os, ")\n");
}


std::string CodeGenerator::get_label_name(s64 some_lab_num) const
{
	std::string ret = sconcat(some_lab_num);

	// Don't have any labels with the same identifier as any functions
	do
	{
		ret = sconcat("_", ret);
	} while (__frontend->__func_tbl.contains(cstm_strdup(ret)));

	return ret;
}
