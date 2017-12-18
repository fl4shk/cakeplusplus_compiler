#ifndef vm_code_class_hpp
#define vm_code_class_hpp

#include "misc_includes.hpp"
//#include "allocation_stuff.hpp"

enum class VmInstrOp : u16
{
	constant,
	constant_u32,
	constant_s32,
	constant_u16,
	constant_s16,
	constant_u8,
	constant_s8,

	arg,
	argx,
	var,
	varx,
	get_pc,
	jump,

	beq,
	bne,
	beq_near,
	bne_near,

	call,
	ret,

	ld_basic,
	ld_u32,
	ld_s32,
	ld_u16,
	ld_s16,
	ld_u8,
	ld_s8,

	ldx_basic,
	ldx_u32,
	ldx_s32,
	ldx_u16,
	ldx_s16,
	ldx_u8,
	ldx_s8,

	st_basic,
	st_u32,
	st_s32,
	st_u16,
	st_s16,
	st_u8,
	st_s8,

	stx_basic,
	stx_u32,
	stx_s32,
	stx_u16,
	stx_s16,
	stx_u8,
	stx_s8,


	add_to_sp,

	add,
	sub,
	mul,
	udiv,
	sdiv,
	umod,
	smod,

	bit_and,
	bit_or,
	bit_xor,
	bit_lsl,
	bit_lsr,
	bit_asr,


	cmp_eq,
	cmp_ne,
	cmp_ult,
	cmp_slt,
	cmp_ugt,
	cmp_sgt,
	cmp_ule,
	cmp_sle,
	cmp_uge,
	cmp_sge,


	//disp_num,
	//disp_num_unsigned,
	//disp_char,
	//disp_str,
	//get_num,
	syscall,

	quit,
};

enum class VmSyscallShorthandOp : u64
{
	disp_num,
	disp_num_unsigned,
	disp_char,
	disp_str,
	get_num,
};

enum class VmUS : bool
{
	Unsgn,
	Sgn,
};

enum class VmLdStType : u32
{
	Basic,
	U32,
	S32,
	U16,
	S16,
	U8,
	S8,
};

class VmCode
{
public:		// variables
	VmInstrOp op;

	VmUS unsgn_or_sgn;
	VmLdStType ldst_type;

	s64 immediate;

	VmCode * next, * prev;
};


#endif		// vm_code_class_hpp
