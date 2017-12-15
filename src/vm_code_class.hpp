#ifndef vm_code_class_hpp
#define vm_code_class_hpp

#include "misc_includes.hpp"
//#include "allocation_stuff.hpp"

enum class VmInstrOp : u16
{
	constant,
	arg,
	argx,
	var,
	varx,
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
	CmpLt,
	CmpGt,
	CmpLe,
	CmpGe,
};

class VmCode
{
public:		// variables
	VmInstrOp op;

	union
	{
		VmInstrLdStOp ldst_op;
		VmInstrBinOp bin_op;
	};

	s64 immediate;

	VmCode * next, * prev;
};


#endif		// vm_code_class_hpp
