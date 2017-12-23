#ifndef ir_code_stuff_hpp
#define ir_code_stuff_hpp

#include "misc_includes.hpp"

typedef std::string* Ident;


// Expression operator
enum class IrExOp
{
	Constant,

	// Binary operator
	Binop,

	// Unary operator
	Unop,

	// Symbol reference
	RefSym,

	// Function reference
	RefFunc,

	// Label reference
	RefLab,

	// Length of symbol
	Len,

	// Size of symbol
	Sizeof,


	// Call with a return value
	CallWithRet,


	// Memory address (example of use:  grabs address from symbol, 
	Mem,

	// Load
	Ld,

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
};

enum class IrMachineMode
{
	U64,
	S64,
	U32,
	S32,
	U16,
	S16,
	U8,
	S8,
};

class IrExpr;

class Function;
class Symbol;

extern IrExpr* mk_ir_expr(IrExpr* some_parent);
extern IrExpr* mk_ir_expr(IrExpr&& to_move);

// This is a tree
class IrExpr
{
public:		// variables
	IrExOp op;

	// Making this a union saves space (perhaps unnecessarily so).
	union
	{
		u64 uimm;
		s64 simm;
		IrBinop binop;
		IrUnop unop;
		Function* func;
		Symbol* sym;
		s64 lab_num;
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
