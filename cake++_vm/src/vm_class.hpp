#ifndef vm_class_hpp
#define vm_class_hpp

#include "misc_includes.hpp"


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
	sdiv,
	udiv,
	smod,
	umod,

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


	disp_num,
	disp_num_unsigned,
	disp_char,
	disp_str,
	get_num,

	quit,
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
	} __regs;


public:		// functions
	Vm(size_t s_mem_size);
	~Vm();


	int run();


private:		// functions
	void exec_one_instr(VmInstrOp& op);

	// pc() incrementers
	VmInstrOp get_op();
	s64 get_imm_64();
	s64 get_imm_u32();
	s64 get_imm_s32();
	s64 get_imm_u16();
	s64 get_imm_s16();
	s64 get_imm_u8();
	s64 get_imm_s8();


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
		printerr("Error (Program counter of ", 
			(__regs.pc - sizeof(u16)), "):  ", msg, "\n");
		exit(1);
	}


};

#endif		// vm_class_hpp
