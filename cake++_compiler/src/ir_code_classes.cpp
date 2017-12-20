#include "ir_code_classes.hpp"


//std::ostream& operator << (std::ostream& os, IrBinop binop)
//{
//	switch (unsgn_or_sgn)
//	{
//		case IrUS::Unsgn:
//			switch (binop)
//			{
//				case IrBinop::Add:
//					return osprintout(os, "add");
//				case IrBinop::Sub:
//					return osprintout(os, "sub");
//				case IrBinop::Mul:
//					return osprintout(os, "mul");
//				case IrBinop::Div:
//					return osprintout(os, "udiv");
//				case IrBinop::Mod:
//					return osprintout(os, "umod");
//
//				case IrBinop::BitAnd:
//					return osprintout(os, "bit_and");
//				case IrBinop::BitOr:
//					return osprintout(os, "bit_or");
//				case IrBinop::BitXor:
//					return osprintout(os, "bit_xor");
//
//				case IrBinop::BitLsl:
//					return osprintout(os, "bit_lsl");
//				case IrBinop::BitLsr:
//					return osprintout(os, "bit_lsr");
//				case IrBinop::BitAsr:
//					return osprintout(os, "bit_asr");
//
//				case IrBinop::CmpEq:
//					return osprintout(os, "cmp_eq");
//				case IrBinop::CmpLt:
//					return osprintout(os, "cmp_ult");
//				case IrBinop::CmpLe:
//					return osprintout(os, "cmp_ule");
//				default:
//					printerr("Binop osprintout thing:  Eek!\n");
//					exit(1);
//			}
//			break;
//		case IrUS::Sgn:
//			switch (binop)
//			{
//				case IrBinop::Add:
//					return osprintout(os, "add");
//				case IrBinop::Sub:
//					return osprintout(os, "sub");
//				case IrBinop::Mul:
//					return osprintout(os, "mul");
//				case IrBinop::Div:
//					return osprintout(os, "sdiv");
//				case IrBinop::Mod:
//					return osprintout(os, "smod");
//
//				case IrBinop::BitAnd:
//					return osprintout(os, "bit_and");
//				case IrBinop::BitOr:
//					return osprintout(os, "bit_or");
//				case IrBinop::BitXor:
//					return osprintout(os, "bit_xor");
//
//				case IrBinop::BitLsl:
//					return osprintout(os, "bit_lsl");
//				case IrBinop::BitLsr:
//					return osprintout(os, "bit_lsr");
//				case IrBinop::BitAsr:
//					return osprintout(os, "bit_asr");
//
//				case IrBinop::CmpEq:
//					return osprintout(os, "cmp_eq");
//				case IrBinop::CmpLt:
//					return osprintout(os, "cmp_slt");
//				case IrBinop::CmpLe:
//					return osprintout(os, "cmp_sle");
//				default:
//					printerr("Binop osprintout thing:  Eek!\n");
//					exit(1);
//			}
//			break;
//	}
//}

std::ostream& operator << (std::ostream& os, 
	IrSyscallShorthandOp syscall_shorthand_op)
{
	switch (syscall_shorthand_op)
	{
		case IrSyscallShorthandOp::DispNum:
			return osprintout(os, "disp_num");
		case IrSyscallShorthandOp::DispNumUnsigned:
			return osprintout(os, "disp_num_unsigned");
		case IrSyscallShorthandOp::DispChar:
			return osprintout(os, "disp_char");
		case IrSyscallShorthandOp::DispStr:
			return osprintout(os, "disp_str");
		case IrSyscallShorthandOp::GetNum:
			return osprintout(os, "get_num");
		default:
			printerr("SyscallShorthandOp osprintout thing:  Eek!\n");
			exit(1);
	}
}
std::ostream& operator << (std::ostream& os, IrUS unsgn_or_sgn)
{
	switch (unsgn_or_sgn)
	{
		case IrUS::Unsgn:
			return osprintout(os, "unsgn");
		case IrUS::Sgn:
			return osprintout(os, "sng");
	}
}

//std::ostream& operator << (std::ostream& os, 
//	IrLdStConstSize ldstconst_size)
//{
//}

IrCode::IrCode()
{
}
IrCode::~IrCode()
{
}
