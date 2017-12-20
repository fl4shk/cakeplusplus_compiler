#ifndef ir_code_classes_hpp
#define ir_code_classes_hpp


#include "misc_includes.hpp"

typedef std::string* Ident;


enum class IrSyscallShorthandOp : u64
{
	DispNum,
	DispNumUnsigned,
	DispChar,
	DispStr,
	GetNum,
};

enum class IrUS : bool
{
	Unsgn,
	Sgn,
};

enum class IrLdStConstSize : u32
{
	Sz64,
	Sz32,
	Sz16,
	Sz8,
};

// Base class for internal representation of code
class IrCode
{
public:		// variables
	
	IrUS unsgn_or_sgn;
	IrLdStConstSize ldstconst_size;
	IrSyscallShorthandOp syscall_shorthand_op;

	Ident var_ident;

	union
	{
		u64 imm_u64;
		s64 imm_s64;
		u32 imm_u32;
		s32 imm_s32;
		u16 imm_u16;
		s16 imm_s16;
		u8 imm_u8;
		s8 imm_s8;
	};

	std::vector<IrCode*> args;

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
