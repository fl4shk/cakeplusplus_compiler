#ifndef src__slash__vm_class_hpp
#define src__slash__vm_class_hpp

// src/vm_class.hpp

#include "misc_includes.hpp"

namespace cakeplusplus
{

class Vm
{
public:		// constants
	static constexpr size_t max_mem_amount = 0x100000000;

public:		// types
	typedef u64 Address;

	class InstrHeader
	{
	private:		// variables
		u8 __group, __oper;

	public:		// functions
		inline InstrHeader(u16 to_copy)
		{
			*this = to_copy;
		}

		inline InstrHeader(const InstrHeader& to_copy) = default;

		inline InstrHeader& operator = (const InstrHeader& to_copy)
			= default;
		inline InstrHeader& operator = (u16 to_copy)
		{
			__group = to_copy >> 8;
			__oper = to_copy;
			return *this;
		}

		size_t num_arg_bytes() const;

		gen_getter_by_val(group)
		gen_getter_by_val(oper)
	};

	enum class InstrGrp0Oper : u8
	{
		Add,
		Sub,
		Mul,
		Udiv,
		Sdiv,
		Umod,
		Smod,
		Uslt,
		Sslt,
		And,
		Or,
		Xor,
		Lsl,
		Lsr,
		Asr,
		Ldux8,
		Ldsx8,
		Ldux16,
		Ldsx16,
		Ldux32,
		Ldsx32,
		Ldx64,
		Stx8,
		Stx16,
		Stx32,
		Stx64,
		Jmpx,
		Jfal,
		Jtru,
	};

	enum class InstrGrp1Oper : u8
	{
		Addi,
		Subi,
		Muli,
		Udivi,
		Sdivi,
		Umodi,
		Smodi,
		Uslti,
		Sslti,
		Andi,
		Ori,
		Xori,
		Lsli,
		Lsri,
		Asri,
		Ldux8i,
		Ldsx8i,
		Ldux16i,
		Ldsx16i,
		Ldux32i,
		Ldsx32i,
		Ldx64i,
		Stx8i,
		Stx16i,
		Stx32i,
		Stx64i,
		Jmpxi,
		Bfal,
		Btru,
	};

	enum class InstrGrp2Oper : u8
	{
		Constu8,
		Consts8,
		Constu16,
		Consts16,
		Constu32,
		Consts32,
		Const,
	};

	enum class InstrGrp3Oper : u8
	{
		Arg,
		Var,
		GetPc,
	};

	enum class InstrGrp4Oper : u8
	{
		Argx,
		Varx,
		AddToSp,
		Call,
		Ret,
		Syscall,
	};


private:		// variables
	size_t __mem_amount;
	std::string __code_filename;

	std::unique_ptr<u8[]> __mem;

	Address __pc, __sp, __fp;

public:		// functions
	Vm(size_t s_mem_amount, const std::string& s_code_filename);
	virtual ~Vm();

	int run();

	gen_getter_by_val(mem_amount)
	gen_getter_by_con_ref(code_filename)

private:		// functions
	u8 get_raw_mem8_at(Address where) const;
	u16 get_raw_mem16_at(Address where) const;
	u32 get_raw_mem32_at(Address where) const;
	u64 get_mem64_at(Address where) const;

	inline u64 get_casted_mem_u8_at(Address where) const
	{
		return static_cast<u64>(static_cast<u8>(get_raw_mem8_at(where)));
	}
	inline s64 get_casted_mem_s8_at(Address where) const
	{
		return static_cast<s64>(static_cast<s8>(get_raw_mem8_at(where)));
	}
	inline u64 get_casted_mem_u16_at(Address where) const
	{
		return static_cast<u64>(static_cast<u16>(get_raw_mem16_at(where)));
	}
	inline s64 get_casted_mem_s16_at(Address where) const
	{
		return static_cast<s64>(static_cast<s16>(get_raw_mem16_at(where)));
	}
	inline u64 get_casted_mem_u32_at(Address where) const
	{
		return static_cast<u64>(static_cast<u32>(get_raw_mem32_at(where)));
	}
	inline s64 get_casted_mem_s32_at(Address where) const
	{
		return static_cast<s64>(static_cast<s32>(get_raw_mem32_at(where)));
	}


	void set_mem8_at(Address where, u8 data);
	void set_mem16_at(Address where, u16 data);
	void set_mem32_at(Address where, u32 data);
	void set_mem64_at(Address where, u64 data);
};

}


#endif		// src__slash__vm_class_hpp
