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

IrMachineMode get_mm_for_binop(IrExpr* a, IrExpr* b)
{
	if (a->mm == b->mm)
	{
		return a->mm;
	}

	//if (((u32)a->mm) < ((u32)b->mm))
	//{
	//	return 
	//}





	const auto a_mm_unsigned = get_unsigned_mm(a->mm);
	const auto b_mm_unsigned = get_unsigned_mm(b->mm);
	const auto a_mm_signed = get_signed_mm(a->mm);
	const auto b_mm_signed = get_signed_mm(b->mm);

	const u32 a_mm_unsigned_u32 = static_cast<u32>(a_mm_unsigned);
	const u32 b_mm_unsigned_u32 = static_cast<u32>(b_mm_unsigned);
	const u32 a_mm_signed_u32 = static_cast<u32>(a_mm_signed);
	const u32 b_mm_signed_u32 = static_cast<u32>(b_mm_signed);

	if ((a->mm == IrMachineMode::Pointer)
		|| (a->mm == IrMachineMode::Length))
	{
		if ((b->mm == IrMachineMode::Pointer)
			|| (b->mm == IrMachineMode::Length))
		{
			return a->mm;
		}
		else
		{
			return b->mm;
		}
	}
	else if ((b->mm == IrMachineMode::Pointer)
		|| (b->mm == IrMachineMode::Length))
	{
		if ((a->mm == IrMachineMode::Pointer)
			|| (a->mm == IrMachineMode::Length))
		{
			return b->mm;
		}
		else
		{
			return a->mm;
		}
	}

	else if ((!mm_is_regular(a->mm)) || (!mm_is_regular(b->mm)))
	{
		err("get_mm_for_binop():  Eek!");
	}

	if (mm_is_unsigned(a->mm) && mm_is_unsigned(b->mm))
	{
		if (a_mm_unsigned_u32 <= b_mm_unsigned_u32)
		{
			return a->mm;
		}
		else
		{
			return b->mm;
		}
	}
	else if (mm_is_unsigned(a->mm) && mm_is_signed(b->mm))
	{
		// Promote to signed
		if (a_mm_unsigned_u32 <= b_mm_unsigned_u32)
		{
			return a_mm_signed;
		}
		else
		{
			return b_mm_signed;
		}
	}
	else if (mm_is_signed(a->mm) && mm_is_unsigned(b->mm))
	{
		// Promote to signed
		if (a_mm_unsigned_u32 <= b_mm_unsigned_u32)
		{
			return a_mm_signed;
		}
		else
		{
			return b_mm_signed;
		}
	}
	else // if (mm_is_signed(a->mm) && mm_is_signed(b->mm))
	{
		if (a_mm_signed_u32 <= b_mm_signed_u32)
		{
			return a->mm;
		}
		else
		{
			return b->mm;
		}
	}


	err("get_mm_for_binop():  Eek (2)!");
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
