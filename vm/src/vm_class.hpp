#ifndef vm_class_hpp
#define vm_class_hpp

#include "misc_includes.hpp"


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



class Vm
{
public:		// typedefs and classes
	typedef u64 Address;

public:		// constants
	//static constexpr size_t max_mem_size = 0x1'0000'0000;
	static constexpr size_t max_mem_size = 0x100000000;
	static constexpr size_t min_mem_size = 0x10000;

private:		// variables
	std::vector<u8> __mem;

	std::string __program;

	//std::stack<s64> __data_stack;

	struct
	{
		Address pc;
		Address sp;
		Address fp;
		Address arg_space;
	} __regs;


public:		// functions
	Vm(size_t s_mem_size);
	~Vm();

	int run();


private:		// functions
	inline auto& regs()
	{
		return __regs;
	}

	inline const auto& regs() const
	{
		return __regs;
	}

	inline auto& pc()
	{
		return regs().pc;
	}
	inline const auto pc() const
	{
		return regs().pc;
	}

	inline auto& sp()
	{
		return regs().sp;
	}
	inline const auto sp() const
	{
		return regs().sp;
	}

	inline auto& fp()
	{
		return regs().fp;
	}
	inline const auto fp() const
	{
		return regs().fp;
	}

	inline auto& arg_space()
	{
		return regs().arg_space;
	}
	inline const auto arg_space() const
	{
		return regs().arg_space;
	}


	void put_program_into_mem();

	inline s64 top() const
	{
		return get_mem_64(sp());
	}

	inline s64 pop()
	{
		sp() -= sizeof(s64);
		const s64 ret = get_mem_64(sp());
		return ret;
	}

	inline void push(s64 to_push)
	{
		set_mem_64(sp(), to_push);
		sp() += sizeof(s64);
	}

	// __mem accessors
	u64 get_mem_64(size_t address) const;
	u64 set_mem_64(size_t address, u64 data);
	u32 get_mem_32(size_t address) const;
	u32 set_mem_32(size_t address, u32 data);
	u16 get_mem_16(size_t address) const;
	u16 set_mem_16(size_t address, u16 data);
	u8 get_mem_8(size_t address) const;
	u8 set_mem_8(size_t address, u8 data);


	inline void err(const std::string& msg) const
	{
		printerr("Error (Program counter of ", __regs.pc, "):  ", msg, 
			"\n");
		exit(1);
	}


};

#endif		// vm_class_hpp
