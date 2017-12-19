#include "vm_code_class.hpp"


VmCode::VmCode()
{
}
VmCode::~VmCode()
{
}


VmRawInstrOp VmCode::raw_op() const
{
	printerr("VmCode::raw_op():  Eek!\n");
	exit(1);
	return static_cast<VmRawInstrOp>(-1);
}

VmRawInstrOp VmOpConstant::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::constant_64;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::constant_u32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::constant_u16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::constant_u8;
				default:
					printerr("VmOpConstant::raw_op():  unsigned Eek!\n");
					exit(1);
			}
			break;
		case VmUS::Sgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::constant_64;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::constant_s32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::constant_s16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::constant_s8;
				default:
					printerr("VmOpConstant::raw_op():  signed Eek!\n");
					exit(1);
			}
			break;
	}
}

VmRawInstrOp VmOpArg::raw_op() const
{
	return VmRawInstrOp::arg;
}

VmRawInstrOp VmOpArgx::raw_op() const
{
	return VmRawInstrOp::argx;
}

VmRawInstrOp VmOpVar::raw_op() const
{
	return VmRawInstrOp::var;
}

VmRawInstrOp VmOpVarx::raw_op() const
{
	return VmRawInstrOp::varx;
}

VmRawInstrOp VmOpGetPc::raw_op() const
{
	return VmRawInstrOp::get_pc;
}

VmRawInstrOp VmOpJump::raw_op() const
{
	return VmRawInstrOp::jump;
}

VmRawInstrOp VmOpBeq::raw_op() const
{
	if (((s64)((s16)imm_s16)) == (imm_s16))
	{
		return VmRawInstrOp::beq_near;
	}
	else
	{
		return VmRawInstrOp::beq;
	}
}

VmRawInstrOp VmOpBne::raw_op() const
{
	if (((s64)((s16)imm_s16)) == (imm_s16))
	{
		return VmRawInstrOp::bne_near;
	}
	else
	{
		return VmRawInstrOp::bne;
	}
}

VmRawInstrOp VmOpCall::raw_op() const
{
	return VmRawInstrOp::call;
}

VmRawInstrOp VmOpRet::raw_op() const
{
	return VmRawInstrOp::ret;
}

VmRawInstrOp VmOpLd::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::ld_basic;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::ld_u32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::ld_u16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::ld_u8;
				default:
					printerr("VmOpLd::raw_op():  unsigned Eek!\n");
					exit(1);
			}
			break;
		case VmUS::Sgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::ld_basic;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::ld_s32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::ld_s16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::ld_s8;
				default:
					printerr("VmOpLd::raw_op():  signed Eek!\n");
					exit(1);
			}
			break;
	}
}

VmRawInstrOp VmOpLdx::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::ldx_basic;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::ldx_u32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::ldx_u16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::ldx_u8;
				default:
					printerr("VmOpLdx::raw_op():  unsigned Eek!\n");
					exit(1);
			}
			break;
		case VmUS::Sgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::ldx_basic;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::ldx_s32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::ldx_s16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::ldx_s8;
				default:
					printerr("VmOpLdx::raw_op():  signed Eek!\n");
					exit(1);
			}
			break;
	}
}

VmRawInstrOp VmOpSt::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::st_basic;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::st_u32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::st_u16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::st_u8;
				default:
					printerr("VmOpSt::raw_op():  unsigned Eek!\n");
					exit(1);
			}
			break;
		case VmUS::Sgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::st_basic;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::st_s32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::st_s16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::st_s8;
				default:
					printerr("VmOpSt::raw_op():  signed Eek!\n");
					exit(1);
			}
			break;
	}
}

VmRawInstrOp VmOpStx::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::stx_basic;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::stx_u32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::stx_u16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::stx_u8;
				default:
					printerr("VmOpStx::raw_op():  unsigned Eek!\n");
					exit(1);
			}
			break;
		case VmUS::Sgn:
			switch (ldstconst_size)
			{
				case VmLdStConstSize::Sz64:
					return VmRawInstrOp::stx_basic;
				case VmLdStConstSize::Sz32:
					return VmRawInstrOp::stx_s32;
				case VmLdStConstSize::Sz16:
					return VmRawInstrOp::stx_s16;
				case VmLdStConstSize::Sz8:
					return VmRawInstrOp::stx_s8;
				default:
					printerr("VmOpStx::raw_op():  signed Eek!\n");
					exit(1);
			}
			break;
	}
}

VmRawInstrOp VmOpAddToSp::raw_op() const
{
	return VmRawInstrOp::add_to_sp;
}

VmRawInstrOp VmOpAdd::raw_op() const
{
	return VmRawInstrOp::add;
}

VmRawInstrOp VmOpSub::raw_op() const
{
	return VmRawInstrOp::sub;
}

VmRawInstrOp VmOpMul::raw_op() const
{
	return VmRawInstrOp::mul;
}

VmRawInstrOp VmOpDiv::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			return VmRawInstrOp::udiv;
		case VmUS::Sgn:
			return VmRawInstrOp::sdiv;
	}
}

VmRawInstrOp VmOpMod::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			return VmRawInstrOp::umod;
		case VmUS::Sgn:
			return VmRawInstrOp::smod;
	}
}

VmRawInstrOp VmOpBitAnd::raw_op() const
{
	return VmRawInstrOp::bit_and;
}

VmRawInstrOp VmOpBitOr::raw_op() const
{
	return VmRawInstrOp::bit_or;
}

VmRawInstrOp VmOpBitXor::raw_op() const
{
	return VmRawInstrOp::bit_xor;
}

VmRawInstrOp VmOpBitLsl::raw_op() const
{
	return VmRawInstrOp::bit_lsl;
}

VmRawInstrOp VmOpBitLsr::raw_op() const
{
	return VmRawInstrOp::bit_lsr;
}

VmRawInstrOp VmOpBitAsr::raw_op() const
{
	return VmRawInstrOp::bit_asr;
}

VmRawInstrOp VmOpCmpEq::raw_op() const
{
	return VmRawInstrOp::cmp_eq;
}

VmRawInstrOp VmOpCmpNe::raw_op() const
{
	return VmRawInstrOp::cmp_ne;
}

VmRawInstrOp VmOpCmpLt::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			return VmRawInstrOp::cmp_ult;
		case VmUS::Sgn:
			return VmRawInstrOp::cmp_slt;
	}
}

VmRawInstrOp VmOpCmpGt::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			return VmRawInstrOp::cmp_ugt;
		case VmUS::Sgn:
			return VmRawInstrOp::cmp_sgt;
	}
}

VmRawInstrOp VmOpCmpLe::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			return VmRawInstrOp::cmp_ule;
		case VmUS::Sgn:
			return VmRawInstrOp::cmp_sle;
	}
}

VmRawInstrOp VmOpCmpGe::raw_op() const
{
	switch (unsgn_or_sgn)
	{
		case VmUS::Unsgn:
			return VmRawInstrOp::cmp_uge;
		case VmUS::Sgn:
			return VmRawInstrOp::cmp_sge;
	}
}

VmRawInstrOp VmOpSyscall::raw_op() const
{
	return VmRawInstrOp::syscall;
}

VmRawInstrOp VmOpQuit::raw_op() const
{
	return VmRawInstrOp::quit;
}

