#ifndef vm_code_class_hpp
#define vm_code_class_hpp

#include "misc_includes.hpp"
//#include "allocation_stuff.hpp"

typedef std::string* Ident;

enum class VmRawInstrOp : u16
{
	constant_64,
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

class VmCode
{
public:		// variables
	VmRawInstrOp raw_op;

	//VmIntermediateOp op;

	//IrUS unsgn_or_sgn;
	//IrLdStConstSize ldstconst_size;
	//IrSyscallShorthandOp syscall_shorthand_op;

	//Ident var_ident;

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

	//std::vector<VmCode*> args;

	// Circular linked list links
	VmCode * next, * prev;

public:		// functions
	VmCode();
	virtual ~VmCode();


	
};


#endif		// vm_code_class_hpp
