#include "ir_code_stuff.hpp"
#include "symbol_table_classes.hpp"

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
		case IrMachineMode::Length:
			return osprintout(os, "length");
	}

	printerr("osprintout of IrMachineMode:  Eek!\n");
	exit(1);
	return os;
}
IrMachineMode convert_builtin_typename_to_mm
	(BuiltinTypename some_builtin_typename)
{
	switch (some_builtin_typename)
	{
		case BuiltinTypename::U64:
			return IrMachineMode::U64;
		case BuiltinTypename::S64:
			return IrMachineMode::S64;

		case BuiltinTypename::U32:
			return IrMachineMode::U32;
		case BuiltinTypename::S32:
			return IrMachineMode::S32;

		case BuiltinTypename::U16:
			return IrMachineMode::U16;
		case BuiltinTypename::S16:
			return IrMachineMode::S16;

		case BuiltinTypename::U8:
			return IrMachineMode::U8;
		case BuiltinTypename::S8:
			return IrMachineMode::S8;

		default:
			err("convert_builtin_typename_to_mm():  Eek!\n");
			break;
	}

	return IrMachineMode::U64;
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
