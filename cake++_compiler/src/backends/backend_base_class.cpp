#include "backend_base_class.hpp"

//BackendBase::BackendBase(std::vector<Function*>&& s_func_vec,
//	FunctionTable* s_func_tbl)
//	: __func_vec(std::move(s_func_vec)), __func_tbl(s_func_tbl)
//{
//}
//
//BackendBase::~BackendBase()
//{
//}
//
//void BackendBase::gen_code()
//{
//	// This is simple enough
//	__gen_startup_code();
//
//
//	for (auto iter : __func_vec)
//	{
//		__curr_func = iter;
//		__gen_one_func_code();
//	}
//}
//
//std::ostream& BackendBase::osprint_code(std::ostream& os)
//{
//	__osprint_one_code(os, &__startup_code);
//
//	for (auto iter : __func_vec)
//	{
//		osprintout(os, *iter->name(), ":\n");
//		osprintout(os, "{\n");
//		__osprint_one_code(os, __func_to_code_start_map.at(iter));
//		osprintout(os, "}\n");
//	}
//
//	return os;
//}
//
//void BackendBase::handle_curr_func_ir_code_and_cleanup_lab_ident()
//{
//	++__curr_func->last_label_num();
//	__cleanup_lab_ident = cstm_strdup(__func_tbl->get_label_name
//		(__curr_func->last_label_num()));
//
//	// Iterate directly through the IrCode of this function
//	for (auto p=__curr_func->ir_code().next;
//		p!=&__curr_func->ir_code();
//		p=p->next)
//	{
//		set_curr_iop(p->iop());
//		//switch (p->iop())
//		switch (curr_iop())
//		{
//			// Store
//			case IrInOp::St:
//				handle_ir_code_st(p);
//				break;
//
//			// Return from subroutine
//			case IrInOp::ReturnExpr:
//				handle_ir_code_return_expr(p);
//				break;
//			case IrInOp::ReturnNothing:
//				handle_ir_code_return_nothing(p);
//				break;
//
//			// Stop the program
//			case IrInOp::Quit:
//				handle_ir_code_quit(p);
//				break;
//
//
//			case IrInOp::Jump:
//				handle_ir_code_jump(p);
//				break;
//
//			// Call form of code, ignoring return value
//			case IrInOp::Call:
//				handle_ir_code_call(p);
//				break;
//
//			case IrInOp::Syscall:
//				handle_ir_code_syscall(p);
//				break;
//			case IrInOp::Label:
//				handle_ir_code_label(p);
//				break;
//
//			default:
//				printerr("BackendBase",
//					"::handle_curr_func_ir_code_and_cleanup_lab_ident():  "
//					"IrInOp Eek!\n");
//				exit(1);
//				break;
//		}
//	}
//}
//
//BackendCodeBase* BackendBase::handle_ir_pure_expr(IrExpr* p)
//{
//	if (!p->is_pure)
//	{
//		printerr("Bug:  BackendBase::handle_ir_pure_expr():  ",
//			"p is not pure!  Eek!\n");
//		exit(1);
//	}
//
//	switch (p->pure_op)
//	{
//		case IrPureExOp::Constant:
//			return __handle_ir_pure_expr_constant(p);
//
//		// Binary operator
//		case IrPureExOp::Binop:
//			return __handle_ir_pure_expr_binop(p);
//
//		// Unary operator
//		case IrPureExOp::Unop:
//			return __handle_ir_pure_expr_unop(p);
//
//		// Length of symbol
//		case IrPureExOp::Len:
//			return __handle_ir_pure_expr_len(p);
//
//		// Size of symbol
//		case IrPureExOp::Sizeof:
//			return __handle_ir_pure_expr_sizeof(p);
//
//
//		// Call with a return value
//		case IrPureExOp::CallWithRet:
//			return __handle_ir_pure_expr_call_with_ret(p);
//
//
//		// Address of array data
//		case IrPureExOp::ArrDataAddress:
//			return __handle_ir_pure_expr_arr_data_address(p);
//
//		// "Real" memory address (example of use:  grabs address from
//		// symbol, function, or label)
//		case IrPureExOp::RealAddress:
//			return __handle_ir_pure_expr_real_address(p);
//
//		// Dereference
//		case IrPureExOp::Deref:
//			return __handle_ir_pure_expr_deref(p);
//
//		case IrPureExOp::Syscall:
//			return __handle_ir_pure_expr_syscall(p);
//
//		// Load
//		case IrPureExOp::Ld:
//			return __handle_ir_pure_expr_ld(p);
//
//
//		// Type Casting
//		case IrPureExOp::Cast:
//			return __handle_ir_pure_expr_cast(p);
//
//		default:
//			printerr("BackendBase::handle_ir_pure_expr():  Eek!\n");
//			exit(1);
//			return nullptr;
//	}
//}
