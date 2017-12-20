#ifndef ir_code_classes_hpp
#define ir_code_classes_hpp


#include "misc_includes.hpp"

typedef std::string* Ident;

// Type of internal representation operator
enum class IrOp
{
	// Constant number
	Constant,

	// Get address of argument or local variable
	// Takes an index as argument
	// The index does not have to be constant
	Argx,
	Varx,

	// Binary operator
	Binop,


	// Label, given a number
	Label,

	// Conditional branch to a label
	Beq,
	Bne,

	// Unconditional jump to a label
	Jump,

	// Indexed load or store, with size and unsigned/signed determined by
	// the symbol.
	Ldx,

	// Store indexed takes as its argument an identifier, 
	Stx,

	Call,
	RetExpr,
	RetNothing,


	Syscall,
	Quit,
};

enum class IrBinOp
{
	Add,
	Sub,
	Mul,
	Div,
	Mod,

	BitAnd,
	BitOr,
	BitXor,

	BitLsl,
	BitLsr,
	BitAsr,

	CmpEq,
	CmpLt,
	CmpLe,

};

enum class IrSyscallShorthandOp : u64
{
	DispNum,
	DispNumUnsigned,
	DispChar,
	DispStr,
	GetNum,
};

// Unsigned or signed:  Used for binop
enum class IrUS : bool
{
	Unsgn,
	Sgn,
};

//enum class IrLdStConstSize : u32
//{
//	Sz64,
//	Sz32,
//	Sz16,
//	Sz8,
//};

// Base class for internal representation of code
class IrCode
{
public:		// variables
	IrOp op;

	IrBinOp binop;
	IrUS unsgn_or_sgn;

	//IrLdStConstSize ldstconst_size;
	IrSyscallShorthandOp syscall_shorthand_op;

	// Identifier:  used for loads, stores, and calls
	Ident ident;

	// Constant value, or label number
	union
	{
		u64 uimm;
		s64 simm;
	};

	// Arguments
	std::vector<IrCode*> args;

	// Linked list links
	IrCode * next, * prev;

public:		// functions
	IrCode();
	virtual ~IrCode();

	virtual std::string name() const
	{
		printerr("IrCode::name():  Eek!\n");
		exit(1);
		return "IrCode";
	}

};



#endif		// ir_code_classes_hpp
