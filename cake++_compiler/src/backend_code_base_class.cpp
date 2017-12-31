#include "backend_code_base_class.hpp"

#include "backend_base_class.hpp"



std::ostream& BackendBase::osprint_code(std::ostream& os)
{
	__osprint_one_code(os, &__startup_code);

	for (auto iter : __func_vec)
	{
		osprintout(os, *iter->name(), ":\n");
		osprintout(os, "{\n");
		__osprint_one_code(os, __func_to_code_start_map.at(iter));
		osprintout(os, "}\n");
	}

	return os;
}


BackendCodeBase* BackendBase::handle_ir_pure_expr(IrExpr* p)
{
	if (!p->is_pure)
	{
		printerr("Bug:  BackendBase::handle_ir_pure_expr():  ",
			"p is not pure!  Eek!\n");
		exit(1);
	}

	switch (p->pure_op)
	{
		case IrPureExOp::Constant:
			return __handle_ir_pure_expr_constant(p);

		// Binary operator
		case IrPureExOp::Binop:
			return __handle_ir_pure_expr_binop(p);

		// Unary operator
		case IrPureExOp::Unop:
			return __handle_ir_pure_expr_unop(p);

		// Length of symbol
		case IrPureExOp::Len:
			return __handle_ir_pure_expr_len(p);

		// Size of symbol
		case IrPureExOp::Sizeof:
			return __handle_ir_pure_expr_sizeof(p);


		// Call with a return value
		case IrPureExOp::CallWithRet:
			return __handle_ir_pure_expr_call_with_ret(p);


		// Address of array data
		case IrPureExOp::ArrDataAddress:
			return __handle_ir_pure_expr_arr_data_address(p);

		// "Real" memory address (example of use:  grabs address from
		// symbol, function, or label)
		case IrPureExOp::RealAddress:
			return __handle_ir_pure_expr_real_address(p);

		// Load
		case IrPureExOp::Ld:
			return __handle_ir_pure_expr_ld(p);


		// Type Casting
		case IrPureExOp::Cast:
			return __handle_ir_pure_expr_cast(p);

		default:
			printerr("BackendBase::handle_ir_pure_expr():  Eek!\n");
			exit(1);
			return nullptr;
	}
}

