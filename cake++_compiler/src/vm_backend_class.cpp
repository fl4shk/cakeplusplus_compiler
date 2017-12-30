#include "vm_backend_class.hpp"

VmBackend::VmBackend(std::vector<Function*>&& s_func_vec, 
	FunctionTable* s_func_tbl) 
	: BackendBase(std::move(s_func_vec), s_func_tbl)
{
	__startup_code.next = &__startup_code;
	__startup_code.prev = &__startup_code;

	for (auto iter : __func_vec)
	{
		//printout("VmBackend::VmBackend():  ", *iter->name(), "\n");
		//auto vm_code = mk_unlinked_vm_code();
		auto vm_code = static_cast<VmCode*>
			(mk_unlinked_backend_base_code<VmCode>());
		vm_code->next = vm_code;
		vm_code->prev = vm_code;
		__func_to_code_start_map[iter] = vm_code;
	}
}

VmBackend::~VmBackend()
{
	//for (size_t i=0; i<__vm_code_pool.size(); ++i)
	//{
	//	delete __vm_code_pool.at(i);
	//}
}




void VmBackend::__gen_startup_code()
{
	// This function is where global variables should be allocated.
	__curr_func_code = &__startup_code;


	// Allocate space for return value of "main"
	mk_const_u8(0);

	mk_const_func(cstm_strdup("main"));
	mk_call();

	// Use "main"'s return value as the exit code
	mk_quit();
}
void VmBackend::__gen_one_func_code()
{
	//printout("VmBackend::__gen_one_func_code():  Generating VM code for ",
	//	"function with identifier \"", *__curr_func->name(), "\".\n");
	//printout("VmBackend::__gen_one_func_code():  \"", 
	//	*__curr_func->name(), "\"\n");

	__curr_func_code = __func_to_code_start_map.at(__curr_func);


	auto&& args = __curr_func->get_args();
	auto&& local_vars = __curr_func->get_local_vars();

	for (s64 i=0; i<(s64)args.size(); ++i)
	{
		// Simple formula based upon how things are passed:  everything is
		// a 64-bit integer of some sort.
		args.at(i)->var()->set_mem_offset
			(-(i * array_var_dim_storage_size));
	}

	// Every argument is 64-bit.
	// 
	// The only arguments passed by value are
	// those that are scalars of builtin types, and said arguments get
	// casted to 64-bit integers.
	// 
	// All other arguments are passed by reference, and thus a 64-bit
	// pointer is used.
	__arg_space = args.size() * sizeof(u64);

	__ret_val_argx_offset = (-__arg_space);

	__var_space = 0;
	//for (s64 i=0; i<(s64)local_vars.size(); ++i)
	for (auto iter : local_vars)
	{
		iter->var()->set_mem_offset(__var_space);

		//printout("VmBackend::__gen_one_func_code():  ",
		//	"Local variable called \"", *iter->name(), "\" has ",
		//	"mem_offset ", iter->var()->mem_offset(), ".\n");

		if (iter->type() == SymType::ScalarVarName)
		{
			// No extra space allocated besides that which comes directly
			// from the size of the variable itself.
		}
		else if (iter->type() == SymType::ArrayVarName)
		{
			// Allocate space to store number of array elements.
			// This is stored as a uint64_t.
			__var_space += array_var_dim_storage_size;
		}
		else
		{
			printerr("VmBackend::__gen_one_func_code():  ",
				"local var type Eek!\n");
			exit(1);
		}

		// Allocate space for the data.
		__var_space += iter->var()->non_size_used_space();
	}



	//printout("VmBackend::__gen_one_func_code():  ",
	//	"__arg_space, __ret_val_argx_offset, __var_space:  ",
	//	strappcom2(__arg_space, __ret_val_argx_offset, __var_space), "\n");
	



	if (__var_space != 0)
	{
		// Allocate local variables (if any)
		mk_const(__var_space);
		mk_add_to_sp();

		// Fill in dimensions of each local variable array
		for (auto iter : local_vars)
		{
			//if ((iter->type() != SymType::ArrayVarName)
			//	&& (iter->type() == SymType::ArrayClassInstName))
			if (iter->type() != SymType::ArrayVarName)
			{
				if (iter->type() != SymType::ScalarVarName)
				{
					printerr("VmBackend::__gen_one_func_code()  Eek!\n");
					exit(1);
				}
				continue;
			}
			auto var = iter->var();

			// data
			mk_const(var->dim());

			// base
			if (var->mem_offset() != 0)
			{
				// index
				mk_const(var->mem_offset());

				// base
				mk_indexed_var_addr();
			}
			else // if (var->mem_offset() == 0)
			{
				// base
				mk_var_addr();
			}

			// Perform the store
			mk_st_basic();
		}
	}



	handle_curr_func_ir_code_and_cleanup_lab_ident();




	mk_fake_op_label(__cleanup_lab_ident);
	if (__var_space != 0)
	{
		// Deallocate local variables (if any)
		mk_const(-__var_space);
		mk_add_to_sp();
	}


	// return
	mk_ret();

	//printout("\n");
}

std::ostream& VmBackend::__osprint_one_code(std::ostream& os, 
	BackendCodeBase* some_code)
{
	for (auto iter=some_code->next; iter!=some_code; iter=iter->next)
	{
		auto p = static_cast<VmCode*>(iter);

		osprintout(os, "\t");

		if (p->raw_op != VmRawInstrOp::fake_op_label)
		{
			osprintout(os, "\t");
		}

		switch (p->raw_op)
		{
			case VmRawInstrOp::constant_64:
				osprintout(os, "const(");

				if (p->func_ident)
				{
					osprintout(os, *p->func_ident);
				}
				else if (p->lab_ident)
				{
					osprintout(os, *p->lab_ident);
				}
				else
				{
					osprintout(os, p->imm_s64);
				}
				osprintout(os, ")");
				break;
			case VmRawInstrOp::constant_u32:
				osprintout(os, "const_u32(");
				
				if (p->func_ident)
				{
					osprintout(os, *p->func_ident);
				}
				else if (p->lab_ident)
				{
					osprintout(os, *p->lab_ident);
				}
				else
				{
					osprintout(os, (u64)p->imm_u32);
				}
				
				osprintout(os, ")");
				break;
			case VmRawInstrOp::constant_s32:
				osprintout(os, "const_s32(");
				
				if (p->func_ident)
				{
					osprintout(os, *p->func_ident);
				}
				else if (p->lab_ident)
				{
					osprintout(os, *p->lab_ident);
				}
				else
				{
					osprintout(os, (s64)p->imm_s32);
				}
				
				osprintout(os, ")");
				break;
			case VmRawInstrOp::constant_u16:
				osprintout(os, "const_u16(");
				
				if (p->func_ident)
				{
					osprintout(os, *p->func_ident);
				}
				else if (p->lab_ident)
				{
					osprintout(os, *p->lab_ident);
				}
				else
				{
					osprintout(os, (u64)p->imm_u16);
				}
				
				osprintout(os, ")");
				break;
			case VmRawInstrOp::constant_s16:
				osprintout(os, "const_s16(");
				
				if (p->func_ident)
				{
					osprintout(os, *p->func_ident);
				}
				else if (p->lab_ident)
				{
					osprintout(os, *p->lab_ident);
				}
				else
				{
					osprintout(os, (s64)p->imm_s16);
				}
				
				osprintout(os, ")");
				break;
			case VmRawInstrOp::constant_u8:
				osprintout(os, "const_u8(");
				
				if (p->func_ident)
				{
					osprintout(os, *p->func_ident);
				}
				else if (p->lab_ident)
				{
					osprintout(os, *p->lab_ident);
				}
				else
				{
					osprintout(os, (u64)p->imm_u8);
				}
				
				osprintout(os, ")");
				break;
			case VmRawInstrOp::constant_s8:
				osprintout(os, "const_s8(");
				
				if (p->func_ident)
				{
					osprintout(os, *p->func_ident);
				}
				else if (p->lab_ident)
				{
					osprintout(os, *p->lab_ident);
				}
				else
				{
					osprintout(os, (s64)p->imm_s8);
				}
				
				osprintout(os, ")");
				break;

			case VmRawInstrOp::arg:
				osprintout(os, "arg");
				break;
			case VmRawInstrOp::argx:
				osprintout(os, "argx");
				break;
			case VmRawInstrOp::var:
				osprintout(os, "var");
				break;
			case VmRawInstrOp::varx:
				osprintout(os, "varx");
				break;
			case VmRawInstrOp::get_pc:
				osprintout(os, "get_pc");
				break;
			case VmRawInstrOp::jump:
				osprintout(os, "jump");
				break;

			case VmRawInstrOp::beq:
				osprintout(os, "beq(", *p->lab_ident, ")");
				break;
			case VmRawInstrOp::bne:
				osprintout(os, "bne(", *p->lab_ident, ")");
				break;
			case VmRawInstrOp::beq_near:
				osprintout(os, "beq_near(", *p->lab_ident, ")");
				break;
			case VmRawInstrOp::bne_near:
				osprintout(os, "bne_near(", *p->lab_ident, ")");
				break;

			case VmRawInstrOp::call:
				osprintout(os, "call");
				break;
			case VmRawInstrOp::ret:
				osprintout(os, "ret");
				break;

			case VmRawInstrOp::ld_basic:
				osprintout(os, "ld_basic");
				break;
			case VmRawInstrOp::ld_u32:
				osprintout(os, "ld_u32");
				break;
			case VmRawInstrOp::ld_s32:
				osprintout(os, "ld_s32");
				break;
			case VmRawInstrOp::ld_u16:
				osprintout(os, "ld_u16");
				break;
			case VmRawInstrOp::ld_s16:
				osprintout(os, "ld_s16");
				break;
			case VmRawInstrOp::ld_u8:
				osprintout(os, "ld_u8");
				break;
			case VmRawInstrOp::ld_s8:
				osprintout(os, "ld_s8");
				break;

			case VmRawInstrOp::ldx_basic:
				osprintout(os, "ldx_basic");
				break;
			case VmRawInstrOp::ldx_u32:
				osprintout(os, "ldx_u32");
				break;
			case VmRawInstrOp::ldx_s32:
				osprintout(os, "ldx_s32");
				break;
			case VmRawInstrOp::ldx_u16:
				osprintout(os, "ldx_u16");
				break;
			case VmRawInstrOp::ldx_s16:
				osprintout(os, "ldx_s16");
				break;
			case VmRawInstrOp::ldx_u8:
				osprintout(os, "ldx_u8");
				break;
			case VmRawInstrOp::ldx_s8:
				osprintout(os, "ldx_s8");
				break;

			case VmRawInstrOp::st_basic:
				osprintout(os, "st_basic");
				break;
			case VmRawInstrOp::st_u32:
				osprintout(os, "st_u32");
				break;
			case VmRawInstrOp::st_s32:
				osprintout(os, "st_s32");
				break;
			case VmRawInstrOp::st_u16:
				osprintout(os, "st_u16");
				break;
			case VmRawInstrOp::st_s16:
				osprintout(os, "st_s16");
				break;
			case VmRawInstrOp::st_u8:
				osprintout(os, "st_u8");
				break;
			case VmRawInstrOp::st_s8:
				osprintout(os, "st_s8");
				break;

			case VmRawInstrOp::stx_basic:
				osprintout(os, "stx_basic");
				break;
			case VmRawInstrOp::stx_u32:
				osprintout(os, "stx_u32");
				break;
			case VmRawInstrOp::stx_s32:
				osprintout(os, "stx_s32");
				break;
			case VmRawInstrOp::stx_u16:
				osprintout(os, "stx_u16");
				break;
			case VmRawInstrOp::stx_s16:
				osprintout(os, "stx_s16");
				break;
			case VmRawInstrOp::stx_u8:
				osprintout(os, "stx_u8");
				break;
			case VmRawInstrOp::stx_s8:
				osprintout(os, "stx_s8");
				break;


			case VmRawInstrOp::add_to_sp:
				osprintout(os, "add_to_sp");
				break;

			case VmRawInstrOp::add:
				osprintout(os, "add");
				break;
			case VmRawInstrOp::sub:
				osprintout(os, "sub");
				break;
			case VmRawInstrOp::mul:
				osprintout(os, "mul");
				break;
			case VmRawInstrOp::udiv:
				osprintout(os, "udiv");
				break;
			case VmRawInstrOp::sdiv:
				osprintout(os, "sdiv");
				break;
			case VmRawInstrOp::umod:
				osprintout(os, "umod");
				break;
			case VmRawInstrOp::smod:
				osprintout(os, "smod");
				break;

			case VmRawInstrOp::bit_and:
				osprintout(os, "bit_and");
				break;
			case VmRawInstrOp::bit_or:
				osprintout(os, "bit_or");
				break;
			case VmRawInstrOp::bit_xor:
				osprintout(os, "bit_xor");
				break;
			case VmRawInstrOp::bit_lsl:
				osprintout(os, "bit_lsl");
				break;
			case VmRawInstrOp::bit_lsr:
				osprintout(os, "bit_lsr");
				break;
			case VmRawInstrOp::bit_asr:
				osprintout(os, "bit_asr");
				break;


			case VmRawInstrOp::cmp_eq:
				osprintout(os, "cmp_eq");
				break;
			case VmRawInstrOp::cmp_ne:
				osprintout(os, "cmp_ne");
				break;
			case VmRawInstrOp::cmp_ult:
				osprintout(os, "cmp_ult");
				break;
			case VmRawInstrOp::cmp_slt:
				osprintout(os, "cmp_slt");
				break;
			case VmRawInstrOp::cmp_ugt:
				osprintout(os, "cmp_ugt");
				break;
			case VmRawInstrOp::cmp_sgt:
				osprintout(os, "cmp_sgt");
				break;
			case VmRawInstrOp::cmp_ule:
				osprintout(os, "cmp_ule");
				break;
			case VmRawInstrOp::cmp_sle:
				osprintout(os, "cmp_sle");
				break;
			case VmRawInstrOp::cmp_uge:
				osprintout(os, "cmp_uge");
				break;
			case VmRawInstrOp::cmp_sge:
				osprintout(os, "cmp_sge");
				break;


			case VmRawInstrOp::syscall:
				osprintout(os, "syscall");
				break;

			case VmRawInstrOp::quit:
				osprintout(os, "quit");
				break;

			case VmRawInstrOp::fake_op_label:
				osprintout(os, *p->lab_ident, ":");
				break;

			default:
				printerr("Function::osprint_vm_code():  Eek!\n");
				exit(1);
		}
		osprintout(os, "\n");
	}

	//return osprintout(os, "\n");
	return os;
}

BackendCodeBase* VmBackend::__gen_runtime_cast(IrMachineMode some_mm, 
	BackendCodeBase* p, IrExpr* orig_expr)
{
	if (orig_expr->is_pure && (orig_expr->pure_op == IrPureExOp::Ld))
	{
		// The reason for this is that loads already zero-extend or
		// sign-extend as needed.
		return p;
	}

	switch (some_mm)
	{
		case IrMachineMode::U64:
		case IrMachineMode::S64:
			return p;

		case IrMachineMode::U32:
			{
				//auto a = relink_backend_base_code(delink_backend_code_base
				//	(mk_const_u32(0xffff'ffff)), p);
				//return relink_backend_base_code(delink_backend_code_base
				//	(mk_bit_and()), a);
				auto a = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(32)), p);
				auto b = relink_backend_base_code(delink_backend_code_base
					(mk_bit_lsl()), a);
				auto c = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(32)), b);
				return relink_backend_base_code(delink_backend_code_base
					(mk_bit_lsr()), c);
			}
		case IrMachineMode::S32:
			{
				auto a = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(32)), p);
				auto b = relink_backend_base_code(delink_backend_code_base
					(mk_bit_lsl()), a);
				auto c = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(32)), b);
				return relink_backend_base_code(delink_backend_code_base
					(mk_bit_asr()), c);
			}

		case IrMachineMode::U16:
			{
				//auto a = relink_backend_base_code(delink_backend_code_base
				//	(mk_const_u16(0xffff)), p);
				//return relink_backend_base_code(delink_backend_code_base
				//	(mk_bit_and()), a);
				auto a = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(16)), p);
				auto b = relink_backend_base_code(delink_backend_code_base
					(mk_bit_lsl()), a);
				auto c = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(16)), b);
				return relink_backend_base_code(delink_backend_code_base
					(mk_bit_lsr()), c);
			}
		case IrMachineMode::S16:
			{
				auto a = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(16)), p);
				auto b = relink_backend_base_code(delink_backend_code_base
					(mk_bit_lsl()), a);
				auto c = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(16)), b);
				return relink_backend_base_code(delink_backend_code_base
					(mk_bit_asr()), c);
			}

		case IrMachineMode::U8:
			{
				//auto a = relink_backend_base_code(delink_backend_code_base
				//	(mk_const_u8(0xff)), p);
				//return relink_backend_base_code(delink_backend_code_base
				//	(mk_bit_and()), a);
				auto a = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(8)), p);
				auto b = relink_backend_base_code(delink_backend_code_base
					(mk_bit_lsl()), a);
				auto c = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(8)), b);
				return relink_backend_base_code(delink_backend_code_base
					(mk_bit_lsr()), c);
			}
		case IrMachineMode::S8:
			{
				auto a = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(8)), p);
				auto b = relink_backend_base_code(delink_backend_code_base
					(mk_bit_lsl()), a);
				auto c = relink_backend_base_code(delink_backend_code_base
					(mk_const_u8(8)), b);
				return relink_backend_base_code(delink_backend_code_base
					(mk_bit_asr()), c);
			}

		case IrMachineMode::Pointer:
		case IrMachineMode::Length:
			return p;

		default:
			printerr("VmBackend::__gen_runtime_cast():  Eek!\n");
			exit(1);
			return nullptr;
	}
}

BackendCodeBase* VmBackend::__handle_ir_pure_expr_constant(IrExpr* p)
{
	switch (p->mm)
	{
		case IrMachineMode::U64:
			return mk_const(p->uimm);
		case IrMachineMode::S64:
			return mk_const(p->simm);

		case IrMachineMode::U32:
			return mk_const_u32((u32)p->uimm);
		case IrMachineMode::S32:
			return mk_const_s32((s32)p->simm);

		case IrMachineMode::U16:
			return mk_const_u16((u16)p->uimm);
		case IrMachineMode::S16:
			return mk_const_s16((s16)p->simm);

		case IrMachineMode::U8:
			return mk_const_u8((u8)p->uimm);
		case IrMachineMode::S8:
			return mk_const_s8((s8)p->simm);

		case IrMachineMode::Pointer:
		case IrMachineMode::Length:
		default:
			printerr("VmBackend::__handle_ir_pure_expr_constant():  ",
				"Eek!\n");
			exit(1);
			return nullptr;
	}
}
BackendCodeBase* VmBackend::__handle_ir_pure_expr_binop(IrExpr* p)
{
	auto a = p->args.at(0);
	auto b = p->args.at(1);

	auto code_a = handle_ir_pure_expr(a);
	auto code_b = handle_ir_pure_expr(b);

	switch (p->binop)
	{
		case IrBinop::Add:
		case IrBinop::Sub:
		case IrBinop::Mul:
		case IrBinop::Div:
		case IrBinop::Mod:

		// Logical And, Logical Or
		case IrBinop::LogAnd:
			break;
		case IrBinop::LogOr:
			break;

		// Bitwise Functions
		case IrBinop::BitAnd:
		case IrBinop::BitOr:
		case IrBinop::BitXor:

		// Shifts
		case IrBinop::BitShiftLeft:
		case IrBinop::BitShiftRight:
			break;


		// Compares
		case IrBinop::CmpEq:
		case IrBinop::CmpNe:
		case IrBinop::CmpLt:
		case IrBinop::CmpGt:
		case IrBinop::CmpLe:
		case IrBinop::CmpGe:
			code_a = __gen_runtime_cast(a->mm, code_a, a);
			code_b = __gen_runtime_cast(b->mm, code_b, b);
			break;

		default:
			printerr("VmBackend::__handle_ir_pure_expr_binop():  ",
				"(runtime cast stuff) Binop Eek!\n");
			exit(1);
			break;
	}

	const bool is_signed = mm_is_signed(p->mm);


	BackendCodeBase* code_ret;

	if (!is_signed)
	{
		switch (p->binop)
		{
			case IrBinop::Add:
				code_ret = mk_add();
				break;
			case IrBinop::Sub:
				code_ret = mk_sub();
				break;
			case IrBinop::Mul:
				code_ret = mk_mul();
				break;
			case IrBinop::Div:
				code_ret = mk_udiv();
				break;
			case IrBinop::Mod:
				code_ret = mk_umod();
				break;

			// Logical And, Logical Or
			case IrBinop::LogAnd:
				code_ret = mk_bit_and();
				code_ret = mk_const_u8(0);
				code_ret = mk_cmp_ne();
				break;
			case IrBinop::LogOr:
				code_ret = mk_bit_or();
				code_ret = mk_const_u8(0);
				code_ret = mk_cmp_ne();
				break;

			// Bitwise Functions
			case IrBinop::BitAnd:
				code_ret = mk_bit_and();
				break;
			case IrBinop::BitOr:
				code_ret = mk_bit_or();
				break;
			case IrBinop::BitXor:
				code_ret = mk_bit_xor();
				break;

			// Shifts
			case IrBinop::BitShiftLeft:
				code_ret = mk_bit_lsl();
				break;
			case IrBinop::BitShiftRight:
				code_ret = mk_bit_lsr();
				break;


			// Compares
			case IrBinop::CmpEq:
				code_ret = mk_cmp_eq();
				break;
			case IrBinop::CmpNe:
				code_ret = mk_cmp_ne();
				break;
			case IrBinop::CmpLt:
				code_ret = mk_cmp_ult();
				break;
			case IrBinop::CmpGt:
				code_ret = mk_cmp_ugt();
				break;
			case IrBinop::CmpLe:
				code_ret = mk_cmp_ule();
				break;
			case IrBinop::CmpGe:
				code_ret = mk_cmp_uge();
				break;

			default:
				printerr("VmBackend::__handle_ir_pure_expr_binop():  ",
					"Binop Eek!\n");
				exit(1);
				break;
		}
	}
	else // if (is_signed)
	{
		switch (p->binop)
		{
			case IrBinop::Add:
				code_ret = mk_add();
				break;
			case IrBinop::Sub:
				code_ret = mk_sub();
				break;
			case IrBinop::Mul:
				code_ret = mk_mul();
				break;
			case IrBinop::Div:
				code_ret = mk_sdiv();
				break;
			case IrBinop::Mod:
				code_ret = mk_smod();
				break;

			// Logical And, Logical Or
			case IrBinop::LogAnd:
				code_ret = mk_bit_and();
				code_ret = mk_const_u8(0);
				code_ret = mk_cmp_ne();
				break;
			case IrBinop::LogOr:
				code_ret = mk_bit_or();
				code_ret = mk_const_u8(0);
				code_ret = mk_cmp_ne();
				break;

			// Bitwise Functions
			case IrBinop::BitAnd:
				code_ret = mk_bit_and();
				break;
			case IrBinop::BitOr:
				code_ret = mk_bit_or();
				break;
			case IrBinop::BitXor:
				code_ret = mk_bit_xor();
				break;

			// Shifts
			case IrBinop::BitShiftLeft:
				code_ret = mk_bit_lsl();
				break;
			case IrBinop::BitShiftRight:
				code_ret = mk_bit_asr();
				break;


			// Compares
			case IrBinop::CmpEq:
				code_ret = mk_cmp_eq();
				break;
			case IrBinop::CmpNe:
				code_ret = mk_cmp_ne();
				break;
			case IrBinop::CmpLt:
				code_ret = mk_cmp_slt();
				break;
			case IrBinop::CmpGt:
				code_ret = mk_cmp_sgt();
				break;
			case IrBinop::CmpLe:
				code_ret = mk_cmp_sle();
				break;
			case IrBinop::CmpGe:
				code_ret = mk_cmp_sge();
				break;

			default:
				printerr("VmBackend::__handle_ir_pure_expr_binop():  ",
					"Binop Eek!\n");
				exit(1);
				break;
		}
	}

	code_ret = __gen_runtime_cast(p->mm, code_ret, p);

	return code_ret;
}
BackendCodeBase* VmBackend::__handle_ir_pure_expr_unop(IrExpr* p)
{
	auto a = p->args.at(0);

	//auto code_a = __gen_runtime_cast(a->mm, handle_ir_pure_expr(a));
	auto code_a = handle_ir_pure_expr(a);


	BackendCodeBase* code_ret;

	switch (p->unop)
	{
		case IrUnop::BitNot:
			code_ret = mk_const_s8(-1);
			code_ret = mk_bit_xor();
			break;

		case IrUnop::Negate:
			code_ret = mk_const_s8(-1);
			code_ret = mk_bit_xor();
			code_ret = mk_const_u8(1);
			code_ret = mk_add();
			break;

		case IrUnop::LogNot:
			code_ret = __gen_runtime_cast(p->mm, code_a, a);
			code_ret = mk_const_u8(0);
			code_ret = mk_cmp_ne();
			break;

		default:
			printerr("VmBackend::__handle_ir_pure_expr_unop():  ",
				"Unop Eek!\n");
			exit(1);
			code_ret = nullptr;
			break;
	}


	return code_ret;
}
BackendCodeBase* VmBackend::__handle_ir_pure_expr_len(IrExpr* p)
{
	if (p->args.size() != 1)
	{
		printerr("VmBackend::__handle_ir_pure_expr_len():  "
			"wrong number of arguments Eek!\n");
		exit(1);
	}
	auto arg = p->args.front();

	if ((arg->mm != IrMachineMode::Pointer) 
		&& (arg->mm != IrMachineMode::Length))
	{
		printerr("VmBackend::__handle_ir_pure_expr_len():  ",
			"IrMachineMode Eek!\n");
		exit(1);
	}
	if (arg->is_pure)
	{
		printerr("VmBackend::__handle_ir_pure_expr_len():  ",
			"arg->is_pure Eek!\n");
		exit(1);
	}
	if (arg->spec_op != IrSpecExOp::RefSym)
	{
		printerr("VmBackend::__handle_ir_pure_expr_len():  ",
			"arg->spec_op Eek!\n");
		exit(1);
	}

	auto sym = arg->sym;

	switch (sym->type())
	{
		case SymType::ScalarVarName:
			return mk_const_u8(1);

		case SymType::ArrayVarName:
			{
				auto var = sym->var();

				if (var->is_arg())
				{
					__mk_address_of_variable(var);
					return mk_ld_basic();
				}
				else
				{
					return mk_const(sym->var()->dim());
				}
			}

		case SymType::FuncName:
		default:
			printerr("VmBackend::__handle_ir_pure_expr_len():  ",
				"sym->type() Eek!\n");
			exit(1);
			return nullptr;
	}
}
BackendCodeBase* VmBackend::__handle_ir_pure_expr_sizeof(IrExpr* p)
{
	auto arg = p->args.front();

	if ((arg->mm != IrMachineMode::Pointer) 
		&& (arg->mm != IrMachineMode::Length))
	{
		printerr("VmBackend::__handle_ir_pure_expr_sizeof():  ",
			"IrMachineMode Eek!\n");
		exit(1);
	}
	if (arg->is_pure)
	{
		printerr("VmBackend::__handle_ir_pure_expr_sizeof():  ",
			"arg->is_pure Eek!\n");
		exit(1);
	}
	if (arg->spec_op != IrSpecExOp::RefSym)
	{
		printerr("VmBackend::__handle_ir_pure_expr_sizeof():  ",
			"arg->spec_op Eek!\n");
		exit(1);
	}

	auto sym = arg->sym;


	switch (sym->type())
	{
		case SymType::ScalarVarName:
			return mk_const(sym->var()->non_size_used_space());

		case SymType::ArrayVarName:
			{
				auto var = sym->var();

				if (var->is_arg())
				{
					// At runtime, a u64 stores the size of the array
					mk_const_u8(array_var_dim_storage_size);


					// Calculate var->non_size_used_space() at runtime
					// because we don't know at compile time what arrays
					// will be passed to the function.
					// 
					// Fortunately, this is likely to be a really uncommon
					// operation.
						__mk_address_of_variable(var);

						// Load the number of elements from memory...
						mk_ld_basic();

						// ...and multiply it by the size of the type
						mk_const_u8(get_builtin_typename_size
							(var->type()));
					mk_mul();

					// Perform the final add.
					return mk_add();
				}
				else // if (!var->is_arg())
				{
					// Add the space allocated for the size of the array
					return mk_const(array_var_dim_storage_size 
						+ var->non_size_used_space());
				}
			}

		case SymType::FuncName:
		default:
			printerr("VmBackend::__handle_ir_pure_expr_sizeof():  ",
				"sym->type() Eek!\n");
			exit(1);
			return nullptr;
	}
}
BackendCodeBase* VmBackend::__handle_ir_pure_expr_call_with_ret(IrExpr* p)
{
	auto ref_func = p->args.front();

	if (ref_func->is_pure || (ref_func->spec_op != IrSpecExOp::RefSym))
	{
		printerr("VmBackend::__handle_ir_pure_expr_call_with_ret():  ",
			"ref_func:  non-pure or bad spec_op Eek!\n");
		exit(1);
	}
	if (ref_func->sym->type() != SymType::FuncName)
	{
		printerr("VmBackend::__handle_ir_pure_expr_call_with_ret():  ",
			"ref_func->sym->type != SymType::FuncName Eek!\n");
		exit(1);
	}



	// Allocate space for return value (always allocated as 64-bit)
	mk_const_u8(0);


	// p->args.at(0) was the function symbol reference, so it's not an
	// argument to the function
	// 
	// Iterate backwards because of how arguments are set up.
	for (s64 i=p->args.size()-1; i>0; --i)
	{
		handle_ir_pure_expr(p->args.at(i));
	}

	mk_const_func(ref_func->sym->name());
	mk_call();

	const s64 amount_to_subtract_from_sp
		= static_cast<s64>(p->args.size() - static_cast<s64>(1)) 
		* static_cast<s64>(array_var_dim_storage_size);

	// Possible future optimization:  check how big
	// amount_to_subtract_from_sp is and use "mk_const...()" that has
	// smaller immediate value.
	mk_const(-amount_to_subtract_from_sp);
	return mk_add_to_sp();
}
BackendCodeBase* VmBackend::__handle_ir_pure_expr_address(IrExpr* p)
{
	auto a = p->args.at(0);

	if (a->is_pure)
	{
		printerr("VmBackend::__handle_ir_pure_expr_address():  ",
			"a->is_pure Eek!\n");
		exit(1);
	}


	BackendCodeBase* code_ret;

	auto handle_ref_sym = [&]() -> void
	{
		auto sym = a->sym;

		set_ir_code_st_var_is_arg(false);

		switch (sym->type())
		{
			case SymType::ScalarVarName:
				{
					auto var = sym->var();
					set_ir_code_st_var_is_arg(var->is_arg());

					if (var->mem_offset() != 0)
					{
						code_ret = mk_const(var->mem_offset());

						if (var->is_arg())
						{
							code_ret = mk_indexed_arg_addr();
						}
						else // if (!var->is_arg())
						{
							code_ret = mk_indexed_var_addr();
						}
					}
					else // if (var->mem_offset() == 0)
					{
						if (var->is_arg())
						{
							code_ret = mk_arg_addr();
						}
						else // if (!var->is_arg())
						{
							code_ret = mk_var_addr();
						}
					}
				}
				break;

			case SymType::ArrayVarName:
				{
					auto var = sym->var();
					set_ir_code_st_var_is_arg(var->is_arg());


					if (var->is_arg())
					{
						if (var->mem_offset() != 0)
						{
							// Since arrays are passed by reference, we
							// only need to use the argument directly
							code_ret = mk_const(var->mem_offset());

							code_ret = mk_indexed_var_addr();
						}
						else // if (var->mem_offset() == 0)
						{
							code_ret = mk_arg_addr();
						}
					}
					else // if (!var->is_arg())
					{
						// Add sizeof(u64) because of the space
						// allocated for the dimensions of the array
						code_ret = mk_const(array_var_dim_storage_size 
							+ var->mem_offset());

						code_ret = mk_indexed_var_addr();
					}
				}
				break;

			case SymType::FuncName:
				code_ret = mk_const_func(sym->name());
				break;

			default:
				printerr("VmBackend::__handle_ir_pure_expr_address()",
					"::handle_ref_sym():  Eek!\n");
				exit(1);
				code_ret = nullptr;
				break;
		}
	};

	auto handle_ref_lab = [&]() -> void
	{
		code_ret = mk_const_lab(cstm_strdup(__func_tbl->get_label_name(
			(a->lab_num))));
	};

	switch (a->spec_op)
	{
		// Symbol reference
		case IrSpecExOp::RefSym:
			handle_ref_sym();
			break;


		// Label reference
		case IrSpecExOp::RefLab:
			handle_ref_lab();
			break;

		default:
			printerr("VmBackend::__handle_ir_pure_expr_address():  ",
				"a->spec_op Eek!\n");
			exit(1);
			break;
	}

	return code_ret;
}
BackendCodeBase* VmBackend::__handle_ir_pure_expr_ld(IrExpr* p)
{
	auto where = p->args.front();

	handle_ir_pure_expr(where);

	switch (p->mm)
	{
		case IrMachineMode::U64:
		case IrMachineMode::S64:
			return mk_ld_basic();

		case IrMachineMode::U32:
			return mk_ld_u32();
		case IrMachineMode::S32:
			return mk_ld_s32();

		case IrMachineMode::U16:
			return mk_ld_u16();
		case IrMachineMode::S16:
			return mk_ld_s16();

		case IrMachineMode::U8:
			return mk_ld_u8();
		case IrMachineMode::S8:
			return mk_ld_s8();

		case IrMachineMode::Pointer:
		case IrMachineMode::Length:
		default:
			printerr("VmBackend::__handle_ir_pure_expr_ld():  Eek!\n");
			exit(1);
			return nullptr;
	}
}
BackendCodeBase* VmBackend::__handle_ir_pure_expr_cast(IrExpr* p)
{
	auto what = p->args.front();

	return __gen_runtime_cast(p->mm, handle_ir_pure_expr(what), what);
}



BackendCodeBase* VmBackend::handle_ir_code_st(IrCode* p)
{
	//switch (p->st_mm())
	//{
	//}

	//const auto sym_type = p->sym->type();

	//auto var = p->sym->var();

	auto where = p->args().at(0);
	auto expr = p->args().at(1);

	// where needs to be handled second due to how stores work now.


	set_ir_code_is_st(true);

	auto code_expr = handle_ir_pure_expr(expr);

	set_expr_is_st_address(true);
	handle_ir_pure_expr(where);
	set_expr_is_st_address(false);

	set_ir_code_is_st(false);

	switch (p->st_mm())
	{
		case IrMachineMode::U64:
		case IrMachineMode::S64:
			return mk_st_basic();

		case IrMachineMode::U32:
			if (!ir_code_st_var_is_arg())
			{
				return mk_st_u32();
			}
			else
			{
				__gen_runtime_cast(p->st_mm(), code_expr, expr);
				return mk_st_basic();
			}
		case IrMachineMode::S32:
			if (!ir_code_st_var_is_arg())
			{
				return mk_st_s32();
			}
			else
			{
				__gen_runtime_cast(p->st_mm(), code_expr, expr);
				return mk_st_basic();
			}

		case IrMachineMode::U16:
			if (!ir_code_st_var_is_arg())
			{
				return mk_st_u16();
			}
			else
			{
				__gen_runtime_cast(p->st_mm(), code_expr, expr);
				return mk_st_basic();
			}
		case IrMachineMode::S16:
			if (!ir_code_st_var_is_arg())
			{
				return mk_st_s16();
			}
			else
			{
				__gen_runtime_cast(p->st_mm(), code_expr, expr);
				return mk_st_basic();
			}

		case IrMachineMode::U8:
			if (!ir_code_st_var_is_arg())
			{
				return mk_st_u8();
			}
			else
			{
				__gen_runtime_cast(p->st_mm(), code_expr, expr);
				return mk_st_basic();
			}
		case IrMachineMode::S8:
			if (!ir_code_st_var_is_arg())
			{
				return mk_st_s8();
			}
			else
			{
				__gen_runtime_cast(p->st_mm(), code_expr, expr);
				return mk_st_basic();
			}

		case IrMachineMode::Pointer:
		case IrMachineMode::Length:
		default:
			printerr("VmBackend::handle_ir_code_st():  Eek!\n");
			exit(1);
			return nullptr;
	}
}

BackendCodeBase* VmBackend::handle_ir_code_return_expr(IrCode* p)
{
	auto expr = p->args().front();

	auto code_expr = handle_ir_pure_expr(expr);

	if (__ret_val_argx_offset != 0)
	{
		mk_const(__ret_val_argx_offset);
		mk_indexed_arg_addr();
	}
	else
	{
		mk_arg_addr();
	}

	switch (__curr_func->ret_type())
	{
		case BuiltinTypename::U64:
		case BuiltinTypename::S64:
			//mk_st_basic();
			break;

		case BuiltinTypename::U32:
			//mk_st_u32();
			__gen_runtime_cast(IrMachineMode::U32, code_expr, expr);
			break;
		case BuiltinTypename::S32:
			//mk_st_s32();
			__gen_runtime_cast(IrMachineMode::S32, code_expr, expr);
			break;

		case BuiltinTypename::U16:
			//mk_st_u16();
			__gen_runtime_cast(IrMachineMode::U16, code_expr, expr);
			break;
		case BuiltinTypename::S16:
			//mk_st_s16();
			__gen_runtime_cast(IrMachineMode::S16, code_expr, expr);
			break;

		case BuiltinTypename::U8:
			//mk_st_u8();
			__gen_runtime_cast(IrMachineMode::U8, code_expr, expr);
			break;
		case BuiltinTypename::S8:
			//mk_st_s8();
			__gen_runtime_cast(IrMachineMode::S8, code_expr, expr);
			break;

		default:
			printerr("VmBackend::handle_ir_code_return_expr():  Eek!\n");
			exit(1);
	}

	mk_st_basic();


	mk_const_u8(0);
	return mk_beq_far(__cleanup_lab_ident);
}
BackendCodeBase* VmBackend::handle_ir_code_return_nothing(IrCode* p)
{
	printerr("VmBackend::handle_ir_code_return_nothing():  Eek!\n");
	exit(1);
	return nullptr;
}
BackendCodeBase* VmBackend::handle_ir_code_quit(IrCode* p)
{
	auto val = p->args().front();

	handle_ir_pure_expr(val);

	return mk_quit();
}
BackendCodeBase* VmBackend::handle_ir_code_jump(IrCode* p)
{
	auto where = p->args().front();

	BackendCodeBase* code_ret = nullptr;

	auto handle_ref_lab = [&]() -> void
	{
		mk_const_u8(0);
		code_ret = mk_beq_far(cstm_strdup(__func_tbl->get_label_name
			(where->lab_num)));
	};

	auto handle_ite = [&]() -> void
	{
		auto cond = where->args.at(0);
		handle_ir_pure_expr(cond);

		auto what_if = where->args.at(1);
		auto what_else = where->args.at(2);

		const bool what_if_is_addr = (what_if->is_pure 
			&& (what_if->pure_op == IrPureExOp::Address));
		const bool what_else_is_addr = (what_else->is_pure 
			&& (what_else->pure_op == IrPureExOp::Address));

		if (what_if_is_addr && !what_else_is_addr)
		{
			auto ref_lab = what_if->args.front();
			auto get_next_pc = what_else;

			if (!ref_lab->is_pure 
				&& (ref_lab->spec_op == IrSpecExOp::RefLab))
			{
			}
			else
			{
				printerr("VmBackend::handle_ir_code_jump()",
					"::handle_ite():  Invalid if_then_else Eek!\n");
				exit(1);
			}

			if (!get_next_pc->is_pure
				&& (get_next_pc->spec_op == IrSpecExOp::GetNextPc))
			{
			}
			else
			{
				printerr("VmBackend::handle_ir_code_jump()",
					"::handle_ite():  Invalid if_then_else Eek!\n");
				exit(1);
			}

			code_ret = mk_beq_far(cstm_strdup(__func_tbl->get_label_name
				(ref_lab->lab_num)));
		}
		else if (!what_if_is_addr && what_else_is_addr)
		{
			auto get_next_pc = what_if;
			auto ref_lab = what_else->args.front();

			if (!ref_lab->is_pure 
				&& (ref_lab->spec_op == IrSpecExOp::RefLab))
			{
			}
			else
			{
				printerr("VmBackend::handle_ir_code_jump()",
					"::handle_ite():  Invalid if_then_else Eek!\n");
				exit(1);
			}

			if (!get_next_pc->is_pure
				&& (get_next_pc->spec_op == IrSpecExOp::GetNextPc))
			{
			}
			else
			{
				printerr("VmBackend::handle_ir_code_jump()",
					"::handle_ite():  Invalid if_then_else Eek!\n");
				exit(1);
			}

			code_ret = mk_bne_far(cstm_strdup(__func_tbl->get_label_name
				(ref_lab->lab_num)));
		}
		else
		{
			printerr("VmBackend::handle_ir_code_jump()::handle_ite():  ",
				"Invalid if_then_else Eek!\n");
			exit(1);
		}

	};

	if (where->is_pure)
	{
		printerr("VmBackend::handle_ir_code_jump():  ",
			"where->is_pure Eek!\n");
		exit(1);
		return nullptr;
	}
	else // if (!where->is_pure)
	{
		switch (where->spec_op)
		{
			//// Symbol reference
			//case IrSpecExOp::RefSym:

			//// Function reference
			//case IrSpecExOp::RefFunc:

			// Label reference
			case IrSpecExOp::RefLab:
				handle_ref_lab();
				break;

			//// Sometimes used for the "Else" portion of IfThenElse
			//case IrSpecExOp::GetNextPc:


			// Control flow
			case IrSpecExOp::IfThenElse:
				handle_ite();
				break;

			default:
				printerr("VmBackend::handle_ir_code_jump():  ",
					"where->spec_op Eek!\n");
				exit(1);
				break;
		}
	}

	return code_ret;
}
BackendCodeBase* VmBackend::handle_ir_code_call(IrCode* p)
{
	//return nullptr;
	auto call_expr = p->args().front();
	return handle_ir_pure_expr(call_expr);
}
BackendCodeBase* VmBackend::handle_ir_code_syscall(IrCode* p)
{
	//return nullptr;

	handle_ir_pure_expr(p->args().front());

	mk_const(static_cast<u64>(p->syscall_shorthand_op()));
	return mk_syscall();
}
BackendCodeBase* VmBackend::handle_ir_code_label(IrCode* p)
{
	//return nullptr;
	return mk_fake_op_label(cstm_strdup(__func_tbl->get_label_name
		(p->lab_num())));
}
