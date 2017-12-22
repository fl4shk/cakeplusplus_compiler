#ifndef rtl_stuff_hpp
#define rtl_stuff_hpp

#include "misc_includes.hpp"

typedef std::string* Ident;

enum class RtlType
{
	Instr,

	Jump,
	Call,

	Syscall,
	Label,

};


// Expression operator
enum class RtlExOp
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


	// Call with return value
	CallWithRet,


	// Memory address
	Mem,

	// Load
	Ld,
};

// Instruction operator
enum class RtlInOp
{
	// Store
	St,

	// Control flow
	IfThenElse,

	// Return from subroutine
	ReturnExpr,
	ReturnNothing,

	// Stop the program
	Quit,

	// Nothing (example of use:  sometimes used for the "Else" part of
	// IfThenElse)
	Nil,
};

// Binary operator
enum class RtlBinop
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
enum class RtlUnop
{
	// ~
	BitNot,

	// -
	Negate,

	// !
	LogNot,
};

enum class RtlMachineMode
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

// This is a tree
class RtlExpr
{
public:		// variables
	RtlExOp op;

	union
	{
		RtlBinop binop;
		RtlUnop unop;
	};
	RtlMachineMode mm;

	RtlExpr* parent;
	std::vector<RtlExpr*> children;

public:		// functions
	RtlExpr(RtlExpr* s_parent);
	virtual ~RtlExpr();


};

class RtlCode
{
private:		// variables
	RtlInOp __op;

	std::vector<RtlExpr*> __children;

	std::vector<RtlExpr*> __rtl_expr_pool;


public:		// variables
	// Linked list stuff
	RtlCode * next, * prev;

public:		// functions
	//RtlCode();
	//virtual ~RtlCode();
	//virtual RtlType type();
	//virtual void accept(RtlVisitor& v);

	gen_getter_and_setter_by_val(op);
	gen_getter_by_ref(children);

};


//class RtlInstr : public RtlCode
//{
//public:		// classes
//
//public:		// variables
//	RtlInOp op;
//
//	std::vector<RtlExpr*> children;
//
//
//public:		// functions
//
//};



#endif		// rtl_stuff_hpp