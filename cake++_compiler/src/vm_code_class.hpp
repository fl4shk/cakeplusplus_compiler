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



enum class VmSyscallShorthandOp : u64
{
	DispNum,
	DispNumUnsigned,
	DispChar,
	DispStr,
	GetNum,
};

enum class VmUS : bool
{
	Unsgn,
	Sgn,
};

enum class VmLdStConstSize : u32
{
	Sz64,
	Sz32,
	Sz16,
	Sz8,
};

class VmCode
{
public:		// variables
	//VmRawInstrOp raw_op;

	//VmIntermediateOp op;

	VmUS unsgn_or_sgn;
	VmLdStConstSize ldstconst_size;
	VmSyscallShorthandOp syscall_shorthand_op;

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

	std::vector<VmCode*> args;

	// Circular linked list links
	VmCode * next, * prev;

public:		// functions
	VmCode();
	virtual ~VmCode();

	virtual VmRawInstrOp raw_op() const;

	
};

class VmOpConstant : public VmCode
{
public:		// functions
	inline VmOpConstant()
	{
		//args.resize(0);
	}
	VmRawInstrOp raw_op() const;
};

class VmOpArg : public VmCode
{
public:		// functions
	inline VmOpArg()
	{
		//args.resize(0);
	}
	VmRawInstrOp raw_op() const;

};
class VmOpArgx : public VmCode
{
public:		// functions
	inline VmOpArgx()
	{
		args.resize(1);
	}
	VmRawInstrOp raw_op() const;
	inline auto& index()
	{
		return args.at(0);
	}
};
class VmOpVar : public VmCode
{
public:		// functions
	inline VmOpVar()
	{
		//args.resize(0);
	}
	VmRawInstrOp raw_op() const;
};
class VmOpVarx : public VmCode
{
public:		// functions
	inline VmOpVarx()
	{
		args.resize(1);
	}
	VmRawInstrOp raw_op() const;

	inline auto& index()
	{
		return args.at(0);
	}
};
class VmOpGetPc : public VmCode
{
public:		// functions
	inline VmOpGetPc()
	{
		//args.resize(0);
	}
	VmRawInstrOp raw_op() const;
};
class VmOpJump : public VmCode
{
public:		// functions
	inline VmOpJump()
	{
		args.resize(1);
	}
	VmRawInstrOp raw_op() const;

	inline auto& dest()
	{
		return args.at(0);
	}
};

// Covers beq and beq_near
class VmOpBeq : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};

// Covers bne and bne_near
class VmOpBne : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};

class VmOpCall : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpRet : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};


class VmOpLd : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpLdx : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpSt : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpStx : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};

class VmOpAddToSp : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpAdd : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpSub : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpMul : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpDiv : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpMod : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};

class VmOpBitAnd : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpBitOr : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpBitXor : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpBitLsl : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};

// since ">>" and ">>>" are different operators in the source code,
// this is fine
class VmOpBitLsr : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpBitAsr : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};

class VmOpCmpEq : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpCmpNe : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpCmpLt : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpCmpGt : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpCmpLe : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};
class VmOpCmpGe : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};

class VmOpSyscall : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};

class VmOpQuit : public VmCode
{
public:		// functions
	VmRawInstrOp raw_op() const;
};


#endif		// vm_code_class_hpp
