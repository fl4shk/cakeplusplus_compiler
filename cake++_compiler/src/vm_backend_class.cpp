#include "vm_backend_class.hpp"

VmBackend::VmBackend(std::vector<Function*>&& s_func_vec, 
	FunctionTable* s_func_tbl) 
	: BackendBase(std::move(s_func_vec), s_func_tbl)
{
	__startup_vm_code.next = &__startup_vm_code;
	__startup_vm_code.prev = &__startup_vm_code;

	for (auto iter : __func_vec)
	{
		//printout("VmBackend::VmBackend():  ", *iter->name(), "\n");
		auto vm_code = mk_unlinked_vm_code();
		vm_code->next = vm_code;
		vm_code->prev = vm_code;
		__func_to_code_map[iter] = vm_code;
	}
}

VmBackend::~VmBackend()
{
	//for (size_t i=0; i<__vm_code_pool.size(); ++i)
	//{
	//	delete __vm_code_pool.at(i);
	//}
}

std::ostream& VmBackend::osprint_code(std::ostream& os)
{
	__osprint_one_code(os, __startup_vm_code);

	for (auto iter : __func_vec)
	{
		osprintout(os, *iter->name(), ":\n");
		osprintout(os, "{\n");
		__osprint_one_code(os, *__func_to_code_map.at(iter));
		osprintout(os, "}\n");
	}

	return os;
}



void VmBackend::__gen_startup_code()
{
	//auto func_main = __func_tbl->at("main");
	__curr_vm_code = &__startup_vm_code;


	// Allocate space for return value of "main"
	mk_const_u8(0);

	mk_const_func(cstm_strdup("main"));
	mk_jump();
}
void VmBackend::__gen_one_code()
{
	auto&& args = __curr_func->get_args();
	__curr_vm_code = __func_to_code_map.at(__curr_func);

	//s64 arg_space;


	//s64 ret_val_argx_offset;
	//s64 var_space;


	//// Allocate local variables
	//mk_linked_vm_code(VmRawInstrOp);







	// Deallocate local variables

	// return
}

std::ostream& VmBackend::__osprint_one_code(std::ostream& os, 
	VmCode& some_vm_code)
{
	for (auto p=some_vm_code.next; p!=&some_vm_code; p=p->next)
	{
		osprintout(os, "\t");
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
