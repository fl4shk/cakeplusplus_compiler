#include "ir_code_stuff.hpp"

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
	}

	printerr("osprintout of IrSyscallShorthandOp:  Eek!\n");
	exit(1);
}

std::ostream& operator << (std::ostream& os, IrMachineMode mm)
{
	switch (mm)
	{
		case IrMachineMode::U64:
			return osprintout(os, "u64");
		case IrMachineMode::S64:
			return osprintout(os, "s64");
		case IrMachineMode::U32:
			return osprintout(os, "u32");
		case IrMachineMode::S32:
			return osprintout(os, "s32");
		case IrMachineMode::U16:
			return osprintout(os, "u16");
		case IrMachineMode::S16:
			return osprintout(os, "s16");
		case IrMachineMode::U8:
			return osprintout(os, "u8");
		case IrMachineMode::S8:
			return osprintout(os, "s8");
		case IrMachineMode::Pointer:
			return osprintout(os, "pointer");
	}

	printerr("osprintout of IrMachineMode:  Eek!\n");
	exit(1);
	return os;
}

IrExpr::IrExpr(IrExpr* s_parent)
	: parent(s_parent)
{
}
IrExpr::~IrExpr()
{
}




IrCode::IrCode()
{
}
IrCode::IrCode(IrInOp s_iop)
	: __iop(s_iop)
{
	__iop = s_iop;
}
IrCode::~IrCode()
{
}
