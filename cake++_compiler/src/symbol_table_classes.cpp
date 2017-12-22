#include "symbol_table_classes.hpp"
#include "allocation_stuff.hpp"


//// The symbol table
//SymbolTable sym_tbl;


//void mkscope()
//{
//	sym_tbl.mkscope();
//}
//
//void rmscope()
//{
//	sym_tbl.rmscope();
//}

std::ostream& operator << (std::ostream& os, 
	BuiltinTypename some_builtin_type)
{
	switch (some_builtin_type)
	{
		case BuiltinTypename::Blank:
			return osprintout(os, "Blank");
		case BuiltinTypename::U8:
			return osprintout(os, "u8");
		case BuiltinTypename::U16:
			return osprintout(os, "u16");
		case BuiltinTypename::U32:
			return osprintout(os, "u32");
		case BuiltinTypename::U64:
			return osprintout(os, "u64");
		case BuiltinTypename::S8:
			return osprintout(os, "s8");
		case BuiltinTypename::S16:
			return osprintout(os, "s16");
		case BuiltinTypename::S32:
			return osprintout(os, "s32");
		case BuiltinTypename::S64:
			return osprintout(os, "s64");
		default:
			printerr("BuiltinTypename osprintout stuff:  Eek!\n");
			exit(1);
	}

	return os;
}

bool Symbol::is_unsgn_builtin() const
{
	return ((__var_type == BuiltinTypename::U8)
		|| (__var_type == BuiltinTypename::U16)
		|| (__var_type == BuiltinTypename::U32)
		|| (__var_type == BuiltinTypename::U64));
}

bool Symbol::is_sgn_builtin() const
{
	return ((__var_type == BuiltinTypename::S8)
		|| (__var_type == BuiltinTypename::S16)
		|| (__var_type == BuiltinTypename::S32)
		|| (__var_type == BuiltinTypename::S64));
}
s64 Symbol::builtin_type_size() const
{
	switch (var_type())
	{
		case BuiltinTypename::U64:
		case BuiltinTypename::S64:
			return sizeof(u64);
		case BuiltinTypename::U32:
		case BuiltinTypename::S32:
			return sizeof(u32);
		case BuiltinTypename::U16:
		case BuiltinTypename::S16:
			return sizeof(u16);
		case BuiltinTypename::U8:
		case BuiltinTypename::S8:
			return sizeof(u8);
		default:
			return -1;
	}
}
//IrLdStSize Symbol::get_ldst_size() const
//{
//	switch (var_type())
//	{
//		case BuiltinTypename::U64:
//		case BuiltinTypename::S64:
//			return IrLdStSize::Sz64;
//		case BuiltinTypename::U32:
//		case BuiltinTypename::S32:
//			return IrLdStSize::Sz32;
//		case BuiltinTypename::U16:
//		case BuiltinTypename::S16:
//			return IrLdStSize::Sz16;
//		case BuiltinTypename::U8:
//		case BuiltinTypename::S8:
//			return IrLdStSize::Sz8;
//		default:
//			return IrLdStSize::Unknown;
//	}
//}

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

std::vector<Symbol*> Function::get_args() const
{
	std::vector<Symbol*> ret;

	std::map<size_t, Symbol*> arg_pos_to_sym_map;

	size_t num_args = 0;

	{
	const auto& table = __sym_tbl.tree().children.front()->table.table();
	for (const auto& iter : table)
	{
		auto sym = iter.second;

		if (arg_pos_to_sym_map.count(sym->arg_offset()) != 0)
		{
			printerr("Function::get_args():  Eek!\n");
			exit(1);
		}

		arg_pos_to_sym_map[sym->arg_offset()] = sym;

		// Find the highest argument offset
		if (num_args < sym->arg_offset())
		{
			num_args = sym->arg_offset();
		}
	}
	}

	// Increment because no argument symbol keeps track of how many
	// arguments this function accepts
	++num_args;

	for (size_t i=0; i<num_args; ++i)
	{
		ret.push_back(arg_pos_to_sym_map.at(i));
	}

	return ret;
}

Symbol* Function::get_one_arg(size_t some_arg_offset) const
{
	const auto& table = __sym_tbl.tree().children.front()->table.table();

	for (const auto& iter : table)
	{
		if (iter.second->arg_offset() == some_arg_offset)
		{
			return iter.second;
		}
	}

	return nullptr;
}
//s64 Function::irntoi(IrCode* t) const
//{
//	s64 ret = -1;
//
//	for (auto p=__ir_code.next; p!=&__ir_code; p=p->next)
//	{
//		++ret;
//
//		if (p == t)
//		{
//			break;
//		}
//	}
//
//	return ret;
//}

s64 Function::offset_of_vm_code(VmCode* v) const
{
	s64 offset = 0;

	for (auto p=__vm_code.next; p!=&__vm_code; p=p->next)
	{
		if (p == v)
		{
			return offset;
		}

		offset += p->size;
	}
	return -1;
}

void Function::gen_vm_code()
{
	
	// Allocate local variables



	//auto&& tree = gen_ir_tree();








	// Deallocate local variables
}


std::ostream& Function::osprint_vm_code(std::ostream& os)
{
	osprintout(os, *__name, "\n");
	osprintout(os, "{\n");
	for (auto p=__vm_code.next; p!=&__vm_code; p=p->next)
	{
		osprintout(os, "\t");
		switch (p->raw_op)
		{
			case VmRawInstrOp::constant_64:
				osprintout(os, "const(");
				if (!p->func_ident)
				{
					osprintout(os, p->imm_s64);
				}
				else
				{
					osprintout(os, *p->func_ident);
				}
				osprintout(os, ")");
				break;
			case VmRawInstrOp::constant_u32:
				osprintout(os, "const_u32(", (u64)p->imm_u32, ")");
				break;
			case VmRawInstrOp::constant_s32:
				osprintout(os, "const_s32(", (s64)p->imm_s32, ")");
				break;
			case VmRawInstrOp::constant_u16:
				osprintout(os, "const_u16(", (u64)p->imm_u16, ")");
				break;
			case VmRawInstrOp::constant_s16:
				osprintout(os, "const_s16(", (s64)p->imm_s16, ")");
				break;
			case VmRawInstrOp::constant_u8:
				osprintout(os, "const_u8(", (u64)p->imm_u8, ")");
				break;
			case VmRawInstrOp::constant_s8:
				osprintout(os, "const_s8(", (s64)p->imm_s8, ")");
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
	return osprintout(os, "}\n");

	//return osprintout(os, "\n");
}


FunctionTable::FunctionTable()
{
}

FunctionTable::~FunctionTable()
{
}
