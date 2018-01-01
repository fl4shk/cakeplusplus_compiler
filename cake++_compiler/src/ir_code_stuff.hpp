#ifndef ir_code_stuff_hpp
#define ir_code_stuff_hpp

#include "misc_includes.hpp"
//#include "symbol_table_classes.hpp"

typedef std::string* Ident;

// Pure expression operators are those that directly correspond to 
// Frontend::visitExpr() and friends.
// 
// Sometimes these take expression arguments that are "special", 
// **especially** for the cases of IrPureExOp::Len, IrPureExOp::Sizeof,
// IrPureExOp::CallWithRet, IrPureExOp::Address, and IrPureExOp::Ld.
enum class IrPureExOp
{
	Constant,

	// Binary operator
	Binop,

	// Unary operator
	Unop,

	// Length of symbol
	Len,

	// Size of symbol
	Sizeof,


	// Call with a return value
	CallWithRet,


	// Address of array data
	ArrDataAddress,

	// "Real" memory address (example of use:  grabs address from symbol,
	// function, or label)
	RealAddress,


	// Dereference
	Deref,

	Syscall,


	// Load
	Ld,

	// Type Casting
	Cast,
};

// "Spec" is short for "Special".  These are used as arguments to so-called
// "pure" IrExpr's.
enum class IrSpecExOp
{
	// Symbol reference
	RefSym,

	//// Function reference
	//RefFunc,

	// Label reference
	RefLab,

	// Sometimes used for the "Else" portion of IfThenElse
	GetNextPc,


	// Control flow
	IfThenElse,
};

// Instruction operator
enum class IrInOp
{
	// Store
	St,

	// Return from subroutine
	ReturnExpr,
	ReturnNothing,

	// Stop the program
	Quit,


	Jump,

	// Call form of code, ignoring return value
	Call,

	Syscall,
	Label,
};

// Binary operator
enum class IrBinop : u64
{
	Add,
	Sub,
	Mul,
	Div,
	Mod,

	// Logical And, Logical Or
	LogAnd,
	LogOr,

	// Bitwise Functions
	BitAnd,
	BitOr,
	BitXor,

	// Shifts
	BitShiftLeft,
	BitShiftRight,

	//// Rotates (not sure these will ever be generated)
	//BitRotateLeft,
	//BitRotateRight,

	// Compares
	CmpEq,
	CmpNe,
	CmpLt,
	CmpGt,
	CmpLe,
	CmpGe,
};

// Unary operator
enum class IrUnop : u64
{
	// ~
	BitNot,

	// -
	Negate,

	// !
	LogNot,
};

enum class IrSyscallShorthandOp : u64
{
	DispNum,
	DispNumUnsigned,
	DispChar,
	DispStr,
	GetNum,
	GetNumUnsigned,
	GetChar,
};

enum class IrMachineMode : u32
{
	U64,
	S64,

	U32,
	S32,

	U16,
	S16,

	U8,
	S8,

	Pointer,
	Length,
};

std::ostream& operator << (std::ostream& os, 
	IrSyscallShorthandOp syscall_shorthand_op);
std::ostream& operator << (std::ostream& os, IrMachineMode mm);

enum class BuiltinTypename : u32;
IrMachineMode convert_builtin_typename_to_mm
	(BuiltinTypename some_builtin_typename);

inline bool mm_is_unsigned (IrMachineMode some_mm)
{
	return ((some_mm == IrMachineMode::U64)
		|| (some_mm == IrMachineMode::U32)
		|| (some_mm == IrMachineMode::U16)
		|| (some_mm == IrMachineMode::U8));
}
inline bool mm_is_signed (IrMachineMode some_mm)
{
	return ((some_mm == IrMachineMode::S64)
		|| (some_mm == IrMachineMode::S32)
		|| (some_mm == IrMachineMode::S16)
		|| (some_mm == IrMachineMode::S8));
}
inline bool mm_is_regular(IrMachineMode some_mm)
{
	return (mm_is_unsigned(some_mm) || mm_is_signed(some_mm));
}
inline IrMachineMode get_unsigned_mm(IrMachineMode some_mm)
{
	u32 temp = (u32)some_mm;

	// Clear bit 0
	temp &= ~0x1;

	return (IrMachineMode)temp;
}
inline IrMachineMode get_signed_mm(IrMachineMode some_mm)
{
	u32 temp = (u32)some_mm;

	// Set bit 0
	temp |= 0x1;

	return (IrMachineMode)temp;
}

class IrExpr;

class Function;
class Symbol;

extern IrExpr* mk_ir_expr(IrExpr* some_parent);
extern IrExpr* mk_ir_expr(IrExpr&& to_move);

// This is a tree
class IrExpr
{
public:		// variables
	union
	{
		IrPureExOp pure_op;
		IrSpecExOp spec_op;
	};
	bool is_pure;

	// Making this a union saves space (perhaps unnecessarily so).
	union
	{
		u64 uimm;
		s64 simm;
		IrBinop binop;
		IrUnop unop;
		//Function* func;
		Symbol* sym;
		s64 lab_num;
		IrSyscallShorthandOp syscall_shorthand_op;
	};
	IrMachineMode mm;

	IrExpr* parent;
	std::vector<IrExpr*> args;

public:		// functions
	inline IrExpr()
		: parent(nullptr)
	{
	}
	IrExpr(IrExpr* s_parent);

	IrExpr(IrExpr&& to_move) = default;

	virtual ~IrExpr();

	IrExpr& operator = (IrExpr&& to_move) = default;

	inline auto append_arg(IrExpr* to_append)
	{
		if (to_append->parent != nullptr)
		{
			printerr("IrExpr::append_arg():  Eek!\n");
			exit(1);
		}
		to_append->parent = this;
		args.push_back(to_append);
		return args.back();
	}
	//inline auto append_arg()
	inline auto mk_arg()
	{
		args.push_back(mk_ir_expr(this));
		return args.back();
	}
};

IrMachineMode get_mm_for_binop(IrExpr* a, IrExpr* b);


class IrCode
{
private:		// variables
	IrInOp __iop;

	// IrMachineMode for IrInOp::St 
	IrMachineMode __st_mm;

	union
	{
		IrSyscallShorthandOp __syscall_shorthand_op;
		s64 __lab_num;
	};

	std::vector<IrExpr*> __args;


public:		// variables
	// Linked list stuff
	IrCode * next, * prev;

public:		// functions
	IrCode();
	IrCode(IrInOp s_iop);
	virtual ~IrCode();

	//inline auto append_arg(IrExpr&& to_append)
	//{
	//	__args.push_back(mk_ir_expr(std::move(to_append)));
	//	return __args.back();
	//}
	inline auto append_arg(IrExpr* to_append)
	{
		__args.push_back(to_append);
		return __args.back();
	}
	inline auto mk_arg()
	{
		__args.push_back(mk_ir_expr(nullptr));
		return __args.back();
	}

	gen_getter_and_setter_by_val(iop);
	gen_getter_and_setter_by_val(st_mm);
	gen_getter_and_setter_by_val(syscall_shorthand_op);
	gen_getter_and_setter_by_val(lab_num);
	gen_getter_by_ref(args);

};

#endif		// ir_code_stuff_hpp
