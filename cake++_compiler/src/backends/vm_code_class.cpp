#include "vm_code_class.hpp"


VmCode::VmCode()
{
	//func_ident = nullptr;
	//lab_ident = nullptr;
}
VmCode::~VmCode()
{
}



size_t VmCode::size() const
{
	switch (raw_op)
	{
		case VmRawInstrOp::constant_64:
			return (sizeof(u16) +  sizeof(u64));
		case VmRawInstrOp::constant_u32:
			//p->size += sizeof(u32);
			return (sizeof(u16) + sizeof(u32));
		case VmRawInstrOp::constant_s32:
			//p->size += sizeof(s32);
			return (sizeof(u16) + sizeof(s32));
		case VmRawInstrOp::constant_u16:
			//p->size += sizeof(u16);
			return (sizeof(u16) + sizeof(u16));
		case VmRawInstrOp::constant_s16:
			//p->size += sizeof(s16);
			return (sizeof(u16) + sizeof(s16));
		case VmRawInstrOp::constant_u8:
			//p->size += sizeof(u8);
			return (sizeof(u16) + sizeof(u8));
		case VmRawInstrOp::constant_s8:
			//p->size += sizeof(s8);
			return (sizeof(u16) + sizeof(s8));

		case VmRawInstrOp::arg:
		case VmRawInstrOp::argx:
		case VmRawInstrOp::var:
		case VmRawInstrOp::varx:
		case VmRawInstrOp::get_pc:
		case VmRawInstrOp::jump:
			return sizeof(u16);

		case VmRawInstrOp::beq:
		case VmRawInstrOp::bne:
			//p->size += sizeof(s64);
			return (sizeof(u16) + sizeof(s64));
		case VmRawInstrOp::beq_near:
		case VmRawInstrOp::bne_near:
			//p->size += sizeof(s16);
			return (sizeof(u16) + sizeof(s16));

		case VmRawInstrOp::call:
		case VmRawInstrOp::ret:
			return sizeof(u16);

		case VmRawInstrOp::ld_basic:
		case VmRawInstrOp::ld_u32:
		case VmRawInstrOp::ld_s32:
		case VmRawInstrOp::ld_u16:
		case VmRawInstrOp::ld_s16:
		case VmRawInstrOp::ld_u8:
		case VmRawInstrOp::ld_s8:
			return sizeof(u16);

		case VmRawInstrOp::ldx_basic:
		case VmRawInstrOp::ldx_u32:
		case VmRawInstrOp::ldx_s32:
		case VmRawInstrOp::ldx_u16:
		case VmRawInstrOp::ldx_s16:
		case VmRawInstrOp::ldx_u8:
		case VmRawInstrOp::ldx_s8:
			return sizeof(u16);

		case VmRawInstrOp::st_basic:
		case VmRawInstrOp::st_u32:
		case VmRawInstrOp::st_s32:
		case VmRawInstrOp::st_u16:
		case VmRawInstrOp::st_s16:
		case VmRawInstrOp::st_u8:
		case VmRawInstrOp::st_s8:
			return sizeof(u16);

		case VmRawInstrOp::stx_basic:
		case VmRawInstrOp::stx_u32:
		case VmRawInstrOp::stx_s32:
		case VmRawInstrOp::stx_u16:
		case VmRawInstrOp::stx_s16:
		case VmRawInstrOp::stx_u8:
		case VmRawInstrOp::stx_s8:
			return sizeof(u16);


		case VmRawInstrOp::add_to_sp:
			return sizeof(u16);

		case VmRawInstrOp::add:
		case VmRawInstrOp::sub:
		case VmRawInstrOp::mul:
		case VmRawInstrOp::udiv:
		case VmRawInstrOp::sdiv:
		case VmRawInstrOp::umod:
		case VmRawInstrOp::smod:
			return sizeof(u16);

		case VmRawInstrOp::bit_and:
		case VmRawInstrOp::bit_or:
		case VmRawInstrOp::bit_xor:
		case VmRawInstrOp::bit_lsl:
		case VmRawInstrOp::bit_lsr:
		case VmRawInstrOp::bit_asr:
			return sizeof(u16);


		case VmRawInstrOp::cmp_eq:
		case VmRawInstrOp::cmp_ne:
		case VmRawInstrOp::cmp_ult:
		case VmRawInstrOp::cmp_slt:
		case VmRawInstrOp::cmp_ugt:
		case VmRawInstrOp::cmp_sgt:
		case VmRawInstrOp::cmp_ule:
		case VmRawInstrOp::cmp_sle:
		case VmRawInstrOp::cmp_uge:
		case VmRawInstrOp::cmp_sge:
			return sizeof(u16);


		case VmRawInstrOp::syscall:
			return sizeof(u16);

		case VmRawInstrOp::quit:
			return sizeof(u16);


		// Labels have no size
		case VmRawInstrOp::fake_op_label:
			//p->size = 0;
			return 0;

		default:
			printerr("VmCode::size():  Eek!\n");
			exit(1);
	}
}
