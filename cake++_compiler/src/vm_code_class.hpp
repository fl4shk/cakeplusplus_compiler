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
	virtual std::string name() const
	{
		printerr("VmCode::name():  Eek!\n");
		exit(1);
		return "VmCode";
	}

	
};

class VmOpConstant : public VmCode
{
public:		// functions
	inline VmOpConstant()
	{
		//args.resize(0);
	}

	inline std::string name() const
	{
		return "Constant";
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

	inline std::string name() const
	{
		return "Arg";
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

	inline std::string name() const
	{
		return "Argx";
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

	inline std::string name() const
	{
		return "Var";
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

	inline std::string name() const
	{
		return "Varx";
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

	inline std::string name() const
	{
		return "GetPc";
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

	inline std::string name() const
	{
		return "Jump";
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
	inline VmOpBeq()
	{
		//args.resize(0);
	}

	inline std::string name() const
	{
		return "Beq";
	}

	VmRawInstrOp raw_op() const;
};

// Covers bne and bne_near
class VmOpBne : public VmCode
{
public:		// functions
	inline VmOpBne()
	{
		//args.resize(0);
	}

	inline std::string name() const
	{
		return "Bne";
	}

	VmRawInstrOp raw_op() const;
};

class VmOpCall : public VmCode
{
public:		// functions
	inline VmOpCall()
	{
		args.resize(1);
	}

	inline std::string name() const
	{
		return "Call";
	}

	VmRawInstrOp raw_op() const;

	inline auto& addr()
	{
		return args.at(0);
	}
};
class VmOpRet : public VmCode
{
public:		// functions
	inline VmOpRet()
	{
		//args.resize(0);
	}

	inline std::string name() const
	{
		return "Ret";
	}

	VmRawInstrOp raw_op() const;
};


class VmOpLd : public VmCode
{
public:		// functions
	inline VmOpLd()
	{
		args.resize(1);
	}

	inline std::string name() const
	{
		return "Ld";
	}

	VmRawInstrOp raw_op() const;

	inline auto& base()
	{
		return args.at(0);
	}
};
class VmOpLdx : public VmCode
{
public:		// functions
	inline VmOpLdx()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "Ldx";
	}

	VmRawInstrOp raw_op() const;

	inline auto& base()
	{
		return args.at(0);
	}
	inline auto& index()
	{
		return args.at(1);
	}
};
class VmOpSt : public VmCode
{
public:		// functions
	inline VmOpSt()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "St";
	}

	VmRawInstrOp raw_op() const;

	inline auto& base()
	{
		return args.at(0);
	}
	inline auto& data()
	{
		return args.at(1);
	}
};
class VmOpStx : public VmCode
{
public:		// functions
	inline VmOpStx()
	{
		args.resize(3);
	}

	inline std::string name() const
	{
		return "Stx";
	}

	VmRawInstrOp raw_op() const;

	inline auto& base()
	{
		return args.at(0);
	}
	inline auto& index()
	{
		return args.at(1);
	}
	inline auto& data()
	{
		return args.at(2);
	}
};

class VmOpAddToSp : public VmCode
{
public:		// functions
	inline VmOpAddToSp()
	{
		args.resize(1);
	}

	inline std::string name() const
	{
		return "AddToSp";
	}

	VmRawInstrOp raw_op() const;

	inline auto& amount()
	{
		return args.at(0);
	}
};
class VmOpAdd : public VmCode
{
public:		// functions
	inline VmOpAdd()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "Add";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpSub : public VmCode
{
public:		// functions
	inline VmOpSub()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "Sub";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpMul : public VmCode
{
public:		// functions
	inline VmOpMul()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "Mul";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpDiv : public VmCode
{
public:		// functions
	inline VmOpDiv()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "Div";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpMod : public VmCode
{
public:		// functions
	inline VmOpMod()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "Mod";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};

class VmOpBitAnd : public VmCode
{
public:		// functions
	inline VmOpBitAnd()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "BitAnd";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpBitOr : public VmCode
{
public:		// functions
	inline VmOpBitOr()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "BitOr";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpBitXor : public VmCode
{
public:		// functions
	inline VmOpBitXor()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "BitXor";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpBitLsl : public VmCode
{
public:		// functions
	inline VmOpBitLsl()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "BitLsl";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};

// since ">>" and ">>>" are different operators in the source code,
// this is fine
class VmOpBitLsr : public VmCode
{
public:		// functions
	inline VmOpBitLsr()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "BitLsr";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpBitAsr : public VmCode
{
public:		// functions
	inline VmOpBitAsr()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "BitAsr";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};

class VmOpCmpEq : public VmCode
{
public:		// functions
	inline VmOpCmpEq()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "CmpEq";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpCmpNe : public VmCode
{
public:		// functions
	inline VmOpCmpNe()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "CmpNe";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpCmpLt : public VmCode
{
public:		// functions
	inline VmOpCmpLt()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "CmpLt";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpCmpGt : public VmCode
{
public:		// functions
	inline VmOpCmpGt()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "CmpGt";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpCmpLe : public VmCode
{
public:		// functions
	inline VmOpCmpLe()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "CmpLe";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};
class VmOpCmpGe : public VmCode
{
public:		// functions
	inline VmOpCmpGe()
	{
		args.resize(2);
	}

	inline std::string name() const
	{
		return "CmpGe";
	}

	VmRawInstrOp raw_op() const;

	inline auto& arg_a()
	{
		return args.at(0);
	}
	inline auto& arg_b()
	{
		return args.at(1);
	}
};

class VmOpSyscall : public VmCode
{
public:		// functions
	inline VmOpSyscall()
	{
		args.resize(1);
	}

	inline std::string name() const
	{
		return "Syscall";
	}

	VmRawInstrOp raw_op() const;

	inline auto& id()
	{
		return args.at(0);
	}
};

class VmOpQuit : public VmCode
{
public:		// functions
	inline VmOpQuit()
	{
		args.resize(1);
	}

	inline std::string name() const
	{
		return "Quit";
	}

	VmRawInstrOp raw_op() const;

	inline auto& exit_code()
	{
		return args.at(0);
	}
};


#endif		// vm_code_class_hpp
