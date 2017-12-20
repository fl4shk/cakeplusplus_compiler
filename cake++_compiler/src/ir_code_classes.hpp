#ifndef ir_code_classes_hpp
#define ir_code_classes_hpp


#include "misc_includes.hpp"

typedef std::string* Ident;

// Type of internal representation operator
enum class IrOp
{
	// Constant number
	Constant,

	//// Get address of argument or local variable
	//// Takes an index as argument
	//// The index does not have to be constant
	//Argx,
	//Varx,

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
	// the symbol's type.

	// Load indexed
	Ldx,

	// Store indexed 
	Stx,

	// Function call (takes an ident as
	Call,

	// return expr;
	RetExpr,

	// return;
	RetNothing,


	Syscall,
	Quit,
};

enum class IrBinop
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

//std::ostream& operator << (std::ostream& os, IrBinop binop);
std::ostream& operator << (std::ostream& os, 
	IrSyscallShorthandOp syscall_shorthand_op);
std::ostream& operator << (std::ostream& os, IrUS unsgn_or_sgn);
//std::ostream& operator << (std::ostream& os, 
//	IrLdStConstSize ldstconst_size);

class Function;

// Base class for internal representation of code
class IrCode
{
public:		// variables
	IrOp op;

	// unsgn_or_sgn is used for binary operators
	IrUS unsgn_or_sgn;

	//IrLdStConstSize ldstconst_size;
	IrSyscallShorthandOp syscall_shorthand_op;

	Function* func = nullptr;


	// Identifier, Binop type, constant value, or label number
	union
	{
		// Identifier:  used for loads, stores, and calls
		Ident ident;

		IrBinop binop;
		u64 uimm;
		s64 simm;
		s64 lab_num;
	};

	// Arguments
	std::vector<IrCode*> args;

	// Linked list links
	IrCode * next, * prev;

public:		// functions
	IrCode();
	virtual ~IrCode();

};




#endif		// ir_code_classes_hpp
