#ifndef assembler_class_hpp
#define assembler_class_hpp

#include "misc_includes.hpp"


enum class VmInstrOp : u16
{
	constant,
	arg,
	argx,
	var,
	varx,
	get_arg_space,
	set_arg_space,
	get_pc,
	jump,
	beq,
	bne,
	call,
	ret,
	ld,
	ldx,
	st,
	stx,

	binop,

	disp_num,
	disp_num_unsigned,
	disp_char,
	disp_str,
	get_num,

	quit,
};

enum class VmInstrLdStOp : u16
{
	Basic,
	U32,
	S32,
	U16,
	S16,
	U8,
	S8
};

enum class VmInstrBinOp : u16
{
	Add,
	Sub,
	Mul,
	SDiv,
	UDiv,
	SMod,
	UMod,

	BitAnd,
	BitOr,
	BitXor,
	BitLsl,
	BitLsr,
	BitAsr,


	CmpEq,
	CmpNe,


	CmpULt,
	CmpSLt,


	CmpUGt,
	CmpSGt,


	CmpULe,
	CmpSLe,


	CmpUGe,
	CmpSGe,
};

class Assembler
{
private:		// variables
	

public:		// functions
	

};



#endif		// assembler_class_hpp
