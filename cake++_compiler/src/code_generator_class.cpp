#include "code_generator_class.hpp"
#include "frontend_class.hpp"


CodeGenerator::CodeGenerator(Frontend* s_frontend)
	: __frontend(s_frontend)
{
}
CodeGenerator::~CodeGenerator()
{
}

IrExpr* CodeGenerator::mk_pure_expr_constant(IrMachineMode s_mm, 
	s64 s_simm)
{
	auto ret = mk_ir_pure_expr(IrPureExOp::Constant, s_mm);

	ret->simm = s_simm;

	return ret;
}
IrExpr* CodeGenerator::mk_pure_expr_binop(IrMachineMode s_mm, 
	IrBinop s_binop, IrExpr* a, IrExpr* b)
{
	{
	// Constant folding
	bool a_init = false, b_init = false;

	u64 a_uimm, b_uimm;
	s64 a_simm, b_simm;
	if (!a->is_pure)
	{
	}
	else if (a->pure_op == IrPureExOp::Constant)
	{
		a_init = true;
		a_uimm = a->uimm;
		a_simm = a->simm;
	}
	else if ((a->pure_op == IrPureExOp::Cast)
		&& (a->args.front()->is_pure) 
		&& (a->args.front()->pure_op == IrPureExOp::Constant))
	{
		// Casting makes things a little tricky, but it's not so bad
		a_init = true;
		switch (a->mm)
		{
			case IrMachineMode::U64:
				a_uimm = (u64)a->args.front()->uimm;
				a_simm = (u64)a->args.front()->simm;
				break;
			case IrMachineMode::S64:
				a_uimm = (s64)a->args.front()->uimm;
				a_simm = (s64)a->args.front()->simm;
				break;

			case IrMachineMode::U32:
				a_uimm = (u32)a->args.front()->uimm;
				a_simm = (u32)a->args.front()->simm;
				break;
			case IrMachineMode::S32:
				a_uimm = (s32)a->args.front()->uimm;
				a_simm = (s32)a->args.front()->simm;
				break;

			case IrMachineMode::U16:
				a_uimm = (u16)a->args.front()->uimm;
				a_simm = (u16)a->args.front()->simm;
				break;
			case IrMachineMode::S16:
				a_uimm = (s16)a->args.front()->uimm;
				a_simm = (s16)a->args.front()->simm;
				break;

			case IrMachineMode::U8:
				a_uimm = (u8)a->args.front()->uimm;
				a_simm = (u8)a->args.front()->simm;
				break;
			case IrMachineMode::S8:
				a_uimm = (s8)a->args.front()->uimm;
				a_simm = (s8)a->args.front()->simm;
				break;

			default:
				printerr("CodeGenerator::mk_expr_binop():  cast a Eek!\n");
				exit(1);
		}
	}

	if (!b->is_pure)
	{
	}
	else if (b->pure_op == IrPureExOp::Constant)
	{
		b_init = true;
		b_uimm = b->uimm;
		b_simm = b->simm;
	}
	else if ((b->pure_op == IrPureExOp::Cast)
		&& b->args.front()->is_pure
		&& (b->args.front()->pure_op == IrPureExOp::Constant))
	{
		b_init = true;
		switch (b->mm)
		{
			case IrMachineMode::U64:
				b_uimm = (u64)b->args.front()->uimm;
				b_simm = (u64)b->args.front()->simm;
				break;
			case IrMachineMode::S64:
				b_uimm = (s64)b->args.front()->uimm;
				b_simm = (s64)b->args.front()->simm;
				break;

			case IrMachineMode::U32:
				b_uimm = (u32)b->args.front()->uimm;
				b_simm = (u32)b->args.front()->simm;
				break;
			case IrMachineMode::S32:
				b_uimm = (s32)b->args.front()->uimm;
				b_simm = (s32)b->args.front()->simm;
				break;

			case IrMachineMode::U16:
				b_uimm = (u16)b->args.front()->uimm;
				b_simm = (u16)b->args.front()->simm;
				break;
			case IrMachineMode::S16:
				b_uimm = (s16)b->args.front()->uimm;
				b_simm = (s16)b->args.front()->simm;
				break;

			case IrMachineMode::U8:
				b_uimm = (u8)b->args.front()->uimm;
				b_simm = (u8)b->args.front()->simm;
				break;
			case IrMachineMode::S8:
				b_uimm = (s8)b->args.front()->uimm;
				b_simm = (s8)b->args.front()->simm;
				break;

			default:
				printerr("CodeGenerator::mk_expr_binop():  cast b Eek!\n");
				exit(1);
		}
	}


	if (a_init && b_init)
	{
		auto ret = mk_ir_pure_expr(IrPureExOp::Constant, s_mm);
		switch (s_mm)
		{
			case IrMachineMode::U64:
				ret->uimm = __eval_binop<u64>(s_binop, (u64)a_uimm,
					(u64)b_uimm);
				return ret;
			case IrMachineMode::S64:
				ret->simm = __eval_binop<s64>(s_binop, (s64)a_simm,
					(s64)b_simm);
				return ret;

			case IrMachineMode::U32:
				ret->uimm = __eval_binop<u32>(s_binop, (u32)a_uimm,
					(u32)b_uimm);
				return ret;
			case IrMachineMode::S32:
				ret->simm = __eval_binop<s32>(s_binop, (s32)a_simm,
					(s32)b_simm);
				return ret;

			case IrMachineMode::U16:
				ret->uimm = __eval_binop<u16>(s_binop, (u16)a_uimm,
					(u16)b_uimm);
				return ret;
			case IrMachineMode::S16:
				ret->simm = __eval_binop<s16>(s_binop, (s16)a_simm,
					(s16)b_simm);
				return ret;

			case IrMachineMode::U8:
				ret->uimm = __eval_binop<u8>(s_binop, (u8)a_uimm,
					(u8)b_uimm);
				return ret;
			case IrMachineMode::S8:
				ret->simm = __eval_binop<s8>(s_binop, (s8)a_simm,
					(s8)b_simm);
				return ret;

			case IrMachineMode::Pointer:
				// No constant folding for pointers
				break;

			case IrMachineMode::Length:
				// No constant folding for lengths
				break;

			default:
				printerr("CodeGenerator::mk_expr_binop():  s_mm Eek!\n");
				exit(1);
				break;
		}
	}
	}

	auto ret = mk_ir_pure_expr(IrPureExOp::Binop, s_mm);

	ret->binop = s_binop;

	ret->append_arg(a);
	ret->append_arg(b);

	return ret;
}
IrExpr* CodeGenerator::mk_pure_expr_unop(IrMachineMode s_mm, IrUnop s_unop, 
	IrExpr* a)
{
	{
	// Constant folding
	bool a_init = false;

	u64 a_uimm;
	s64 a_simm;
	if (!a->is_pure)
	{
	}
	else if (a->pure_op == IrPureExOp::Constant)
	{
		a_init = true;
		a_uimm = a->uimm;
		a_simm = a->simm;
	}
	else if ((a->pure_op == IrPureExOp::Cast)
		&& a->args.front()->is_pure 
		&& (a->args.front()->pure_op == IrPureExOp::Constant))
	{
		a_init = true;
		switch (a->mm)
		{
			case IrMachineMode::U64:
				a_uimm = (u64)a->args.front()->uimm;
				a_simm = (u64)a->args.front()->simm;
				break;
			case IrMachineMode::S64:
				a_uimm = (s64)a->args.front()->uimm;
				a_simm = (s64)a->args.front()->simm;
				break;

			case IrMachineMode::U32:
				a_uimm = (u32)a->args.front()->uimm;
				a_simm = (u32)a->args.front()->simm;
				break;
			case IrMachineMode::S32:
				a_uimm = (s32)a->args.front()->uimm;
				a_simm = (s32)a->args.front()->simm;
				break;

			case IrMachineMode::U16:
				a_uimm = (u16)a->args.front()->uimm;
				a_simm = (u16)a->args.front()->simm;
				break;
			case IrMachineMode::S16:
				a_uimm = (s16)a->args.front()->uimm;
				a_simm = (s16)a->args.front()->simm;
				break;

			case IrMachineMode::U8:
				a_uimm = (u8)a->args.front()->uimm;
				a_simm = (u8)a->args.front()->simm;
				break;
			case IrMachineMode::S8:
				a_uimm = (s8)a->args.front()->uimm;
				a_simm = (s8)a->args.front()->simm;
				break;

			default:
				printerr("CodeGenerator::mk_expr_unop():  cast a Eek!\n");
				exit(1);
		}
	}

	if (a_init)
	{
		auto ret = mk_ir_pure_expr(IrPureExOp::Constant, s_mm);
		switch (s_mm)
		{
			case IrMachineMode::U64:
				ret->uimm = __eval_unop<u64>(s_unop, (u64)a_uimm);
				return ret;
			case IrMachineMode::S64:
				ret->simm = __eval_unop<s64>(s_unop, (s64)a_simm);
				return ret;

			case IrMachineMode::U32:
				ret->uimm = __eval_unop<u32>(s_unop, (u32)a_uimm);
				return ret;
			case IrMachineMode::S32:
				ret->simm = __eval_unop<s32>(s_unop, (s32)a_simm);
				return ret;

			case IrMachineMode::U16:
				ret->uimm = __eval_unop<u16>(s_unop, (u16)a_uimm);
				return ret;
			case IrMachineMode::S16:
				ret->simm = __eval_unop<s16>(s_unop, (s16)a_simm);
				return ret;

			case IrMachineMode::U8:
				ret->uimm = __eval_unop<u8>(s_unop, (u8)a_uimm);
				return ret;
			case IrMachineMode::S8:
				ret->simm = __eval_unop<s8>(s_unop, (s8)a_simm);
				return ret;

			case IrMachineMode::Pointer:
				break;

			case IrMachineMode::Length:
				break;

			default:
				printerr("CodeGenerator::mk_expr_unop():  s_mm Eek!\n");
				exit(1);
				break;
		}
	}

	}

	auto ret = mk_ir_pure_expr(IrPureExOp::Unop, s_mm);

	ret->unop = s_unop;

	ret->append_arg(a);
	return ret;
}
IrExpr* CodeGenerator::mk_pure_expr_len(IrMachineMode s_mm, IrExpr* what)
{
	auto ret = mk_ir_pure_expr(IrPureExOp::Len, s_mm);

	ret->append_arg(what);

	return ret;
}
IrExpr* CodeGenerator::mk_pure_expr_sizeof(IrMachineMode s_mm, 
	IrExpr* what)
{
	auto ret = mk_ir_pure_expr(IrPureExOp::Sizeof, s_mm);

	ret->append_arg(what);

	return ret;
}
IrExpr* CodeGenerator::mk_pure_expr_unfinished_call_with_ret
	(IrMachineMode s_mm, IrExpr* where)
{
	auto ret = mk_ir_pure_expr(IrPureExOp::CallWithRet, s_mm);

	ret->append_arg(where);

	return ret;
}
IrExpr* CodeGenerator::mk_pure_expr_address(IrExpr* where)
{
	auto ret = mk_ir_pure_expr(IrPureExOp::Address, IrMachineMode::Pointer);

	ret->append_arg(where);

	return ret;
}
IrExpr* CodeGenerator::mk_pure_expr_ld(IrMachineMode s_mm, 
	IrExpr* where)
{
	auto ret = mk_ir_pure_expr(IrPureExOp::Ld, s_mm);

	ret->append_arg(where);

	return ret;
}
//IrExpr* CodeGenerator::mk_pure_expr_casted_ld(IrMachineMode s_mm, 
//	IrExpr* where)
//{
//	auto expr = mk_ir_pure_expr(IrPureExOp::Ld, s_mm);
//
//	expr->append_arg(where);
//
//	const bool is_signed = mm_is_signed(s_mm);
//
//	if (!is_signed)
//	{
//		return mk_pure_expr_cast(IrMachineMode::U64, expr);
//	}
//	else // if (is_signed)
//	{
//		return mk_pure_expr_cast(IrMachineMode::S64, expr);
//	}
//}
IrExpr* CodeGenerator::mk_pure_expr_cast(IrMachineMode s_mm, IrExpr* expr)
{
	auto ret = mk_ir_pure_expr(IrPureExOp::Cast, s_mm);

	ret->append_arg(expr);

	return ret;
}

IrExpr* CodeGenerator::mk_spec_expr_ref_sym(Symbol* s_sym)
{
	auto ret = mk_ir_spec_expr(IrSpecExOp::RefSym, IrMachineMode::Pointer);

	ret->sym = s_sym;

	return ret;
}
//IrExpr* CodeGenerator::mk_spec_expr_ref_func(Function* s_func)
//{
//	auto ret = mk_ir_spec_expr(IrSpecExOp::RefFunc, IrMachineMode::Pointer);
//
//	ret->func = s_func;
//
//	return ret;
//}
IrExpr* CodeGenerator::mk_spec_expr_ref_lab(s64 s_lab_num)
{
	auto ret = mk_ir_spec_expr(IrSpecExOp::RefLab, IrMachineMode::Pointer);

	ret->lab_num = s_lab_num;

	return ret;
}

IrExpr* CodeGenerator::mk_spec_expr_get_next_pc()
{
	return mk_ir_spec_expr(IrSpecExOp::GetNextPc, IrMachineMode::Pointer);
}
IrExpr* CodeGenerator::mk_spec_expr_if_then_else(IrMachineMode s_mm, 
	IrExpr* cond, IrExpr* what_if, IrExpr* what_else)
{
	auto ret = mk_ir_spec_expr(IrSpecExOp::IfThenElse, s_mm);

	ret->append_arg(cond);
	ret->append_arg(what_if);
	ret->append_arg(what_else);

	return ret;
}

IrCode* CodeGenerator::mk_code_st(IrMachineMode s_st_mm, IrExpr* where, 
	IrExpr* what)
{
	auto ret = mk_linked_ir_code_for_curr_func(IrInOp::St);

	ret->set_st_mm(s_st_mm);
	ret->append_arg(where);
	ret->append_arg(what);

	return ret;
}
IrCode* CodeGenerator::mk_code_return_expr(IrExpr* expr)
{
	auto ret = mk_linked_ir_code_for_curr_func(IrInOp::ReturnExpr);

	ret->append_arg(expr);

	return ret;
}
IrCode* CodeGenerator::mk_code_return_nothing()
{
	return mk_linked_ir_code_for_curr_func(IrInOp::ReturnNothing);
}
IrCode* CodeGenerator::mk_code_quit(IrExpr* val)
{
	auto ret = mk_linked_ir_code_for_curr_func(IrInOp::Quit);

	ret->append_arg(val);

	return ret;
}
IrCode* CodeGenerator::mk_code_jump(IrExpr* where)
{
	auto ret = mk_linked_ir_code_for_curr_func(IrInOp::Jump);

	ret->append_arg(where);

	return ret;
}
//IrCode* CodeGenerator::mk_code_unfinished_call(IrExpr* where)
//{
//	auto ret = mk_linked_ir_code_for_curr_func(IrInOp::Call);
//
//	ret->append_arg(where);
//
//	return ret;
//}
IrCode* CodeGenerator::mk_code_call(IrExpr* call_expr)
{
	auto ret = mk_linked_ir_code_for_curr_func(IrInOp::Call);

	ret->append_arg(call_expr);

	return ret;
}
IrCode* CodeGenerator::mk_code_unfinished_syscall
	(IrSyscallShorthandOp s_syscall_shorthand_op)
{
	auto ret = mk_linked_ir_code_for_curr_func(IrInOp::Syscall);
	ret->set_syscall_shorthand_op(s_syscall_shorthand_op);
	return ret;
}
IrCode* CodeGenerator::mk_code_unlinked_label()
{
	auto ret = mk_unlinked_ir_code(IrInOp::Label);

	//auto& curr_func = __frontend->curr_func();

	++get_curr_func().last_label_num();
	get_curr_func().num_to_label_map()[get_curr_func().last_label_num()] 
		= ret;
	
	ret->set_lab_num(get_curr_func().last_label_num());

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
				node["_syscall_shorthand_op"] 
					= sconcat(p->syscall_shorthand_op());
				break;
			case IrInOp::Label:
				//osprintout(os, get_label_name(p), ":  ");
				node["__iop"] = "label";
				node["_name"] = __frontend->__func_tbl.get_label_name(p);
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

Function& CodeGenerator::get_curr_func()
{
	return __frontend->curr_func();
}
IrCode* CodeGenerator::mk_linked_ir_code_for_curr_func(IrInOp s_iop)
{
	return ::mk_linked_ir_code(get_curr_func(), s_iop);
}

void CodeGenerator::output_ir_expr_as_json(Json::Value& node, IrExpr* p)
{
	node["_mm"] = sconcat(p->mm);

	if (p->is_pure)
	{
		switch (p->pure_op)
		{
			case IrPureExOp::Constant:
				//osprintout(os, "const", temp,
				//	strappcom2(p->mm, p->simm));
				node["__op"] = "const";
				node["_immediate"] = sconcat(p->simm);
				break;

			// Binary operator
			case IrPureExOp::Binop:
				//osprintout(os, "_binop", temp, p->mm);
				node["__op"] = "binop";

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
			case IrPureExOp::Unop:
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


			// Length of symbol
			case IrPureExOp::Len:
				//osprintout(os, "len", temp, p->mm);
				node["__op"] = "len";
				break;

			// Size of symbol
			case IrPureExOp::Sizeof:
				//osprintout(os, "sizeof", temp, p->mm);
				node["__op"] = "sizeof";
				break;


			// Call with a return value
			case IrPureExOp::CallWithRet:
				//osprintout(os, "call_with_ret", temp, p->mm);
				node["__op"] = "call_with_ret";
				break;


			// Memory address (example of use:  grabs address from symbol, 
			case IrPureExOp::Address:
				//osprintout(os, "address", temp, p->mm);
				node["__op"] = "address";
				break;

			// Load
			case IrPureExOp::Ld:
				//osprintout(os, "ld", temp, p->mm);
				node["__op"] = "ld";
				break;

			// Sometimes used for the "Else" portion of IfThenElse
			case IrPureExOp::Cast:
				node["__op"] = "cast";
				break;

			default:
				printerr("CodeGenerator::output_ir_expr_as_json():  ",
					"IrPureExOp Eek!\n");
				exit(1);
				break;
		}
	}
	else // if (!p->is_pure)
	{
		switch (p->spec_op)
		{
			// Symbol reference
			case IrSpecExOp::RefSym:
				//osprintout(os, "ref_sym", temp,
				//	strappcom2(p->mm, *p->sym->name()));
				node["__op"] = "ref_sym";
				node["_name"] = *p->sym->var()->name();
				break;

			//// Function reference
			//case IrSpecExOp::RefFunc:
			//	///osprintout(os, "ref_func", temp,
			//	///	strappcom2(p->mm, *p->func->name()));
			//	node["__op"] = "ref_func";
			//	node["_name"] = *p->func->name();
			//	break;

			// Label reference
			case IrSpecExOp::RefLab:
				//osprintout(os, "ref_lab", temp,
				//	strappcom2(p->mm, get_label_name(p->lab_num)));
				node["__op"] = "ref_lab";
				node["_name"] = __frontend->__func_tbl.get_label_name
					(p->lab_num);
				break;

			case IrSpecExOp::GetNextPc:
				//osprintout(os, "get_next_pc", temp, p->mm);
				node["__op"] = "get_next_pc";
				break;

			// Control flow
			case IrSpecExOp::IfThenElse:
				//osprintout(os, "if_then_else", temp, p->mm);
				node["__op"] = "if_then_else";
				break;

			default:
				printerr("CodeGenerator::output_ir_expr_as_json():  ",
					"IrSpecExOp Eek!\n");
				exit(1);
				break;
		}
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
