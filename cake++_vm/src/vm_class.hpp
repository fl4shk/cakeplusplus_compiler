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

	enum class ArithLogOper : u8
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
	};

	enum class LoadType : u8
	{
		U8,
		S8,
		U16,
		S16,
		U32,
		S32,
		Any64
	};

	enum class StoreType : u8
	{
		Any8,
		Any16,
		Any32,
		Any64
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

		Invalid,
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

		Invalid,
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

		Invalid,
	};

	enum class InstrGrp3Oper : u8
	{
		Arg,
		Var,
		GetPc,

		Invalid,
	};

	enum class InstrGrp4Oper : u8
	{
		Argx,
		Varx,
		AddToSp,
		Call,
		Ret,
		Syscall,

		Invalid,
	};

	enum class SystemCall : u64
	{
		DispChar,
		DispStr,
		DispUInt,
		DispSInt,
		Exit
	};

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
		bool arg_is_signed() const;
		bool valid() const;

		gen_getter_by_val(group)
		gen_getter_by_val(oper)
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
	template<typename... ArgTypes>
	inline void err(ArgTypes&&... args) const
	{
		printerr(std::hex, "Error (pc:  0x",  __pc, ", sp:  0x", __sp,
			", fp:  0x", __fp, "):  ", std::dec, args...);
		printerr("\n");
		exit(1);
	}

	u8 get_raw_mem8_at(Address where) const;
	u16 get_raw_mem16_at(Address where) const;
	u32 get_raw_mem32_at(Address where) const;
	u64 get_mem64_at(Address where) const;

	inline u64 get_extended_mem_u8_at(Address where) const
	{
		return static_cast<u64>(static_cast<u8>(get_raw_mem8_at(where)));
	}
	inline s64 get_extended_mem_s8_at(Address where) const
	{
		return static_cast<s64>(static_cast<s8>(get_raw_mem8_at(where)));
	}
	inline u64 get_extended_mem_u16_at(Address where) const
	{
		return static_cast<u64>(static_cast<u16>(get_raw_mem16_at(where)));
	}
	inline s64 get_extended_mem_s16_at(Address where) const
	{
		return static_cast<s64>(static_cast<s16>(get_raw_mem16_at(where)));
	}
	inline u64 get_extended_mem_u32_at(Address where) const
	{
		return static_cast<u64>(static_cast<u32>(get_raw_mem32_at(where)));
	}
	inline s64 get_extended_mem_s32_at(Address where) const
	{
		return static_cast<s64>(static_cast<s32>(get_raw_mem32_at(where)));
	}

	inline InstrHeader ld_instr_header_and_inc_pc()
	{
		const InstrHeader ret(get_raw_mem16_at(__pc));
		__pc += sizeof(u16);
		return ret;
	}

	inline u64 ldu8_extended_and_inc_pc()
	{
		const auto ret = get_extended_mem_u8_at(__pc);
		__pc += sizeof(u8);
		return ret;
	}
	inline s64 lds8_extended_and_inc_pc()
	{
		const auto ret = get_extended_mem_s8_at(__pc);
		__pc += sizeof(s8);
		return ret;
	}
	inline u64 ldu16_extended_and_inc_pc()
	{
		const auto ret = get_extended_mem_u16_at(__pc);
		__pc += sizeof(u16);
		return ret;
	}
	inline s64 lds16_extended_and_inc_pc()
	{
		const auto ret = get_extended_mem_s16_at(__pc);
		__pc += sizeof(s16);
		return ret;
	}
	inline u64 ldu32_extended_and_inc_pc()
	{
		const auto ret = get_extended_mem_u32_at(__pc);
		__pc += sizeof(u32);
		return ret;
	}
	inline s64 lds32_extended_and_inc_pc()
	{
		const auto ret = get_extended_mem_s32_at(__pc);
		__pc += sizeof(s32);
		return ret;
	}
	inline u64 ld64_and_inc_pc()
	{
		const auto ret = get_mem64_at(__pc);
		__pc += sizeof(u64);
		return ret;
	}


	void set_mem8_at(Address where, u8 data);
	void set_mem16_at(Address where, u16 data);
	void set_mem32_at(Address where, u32 data);
	void set_mem64_at(Address where, u64 data);

	inline u64 pop()
	{
		__sp += sizeof(u64);
		const u64 ret = get_mem64_at(__sp);

		return ret;
	}
	inline void push(u64 to_push)
	{
		set_mem64_at(__sp, to_push);
		__sp -= sizeof(u64);
	}

	void handle_instr_from_group_0(u8 oper, u64 extended_arg);
	void handle_instr_from_group_1(u8 oper, u64 extended_arg);
	void handle_instr_from_group_2(u8 oper, u64 extended_arg);
	void handle_instr_from_group_3(u8 oper, u64 extended_arg);
	void handle_instr_from_group_4(u8 oper, u64 extended_arg);

	void exec_arithlog_instr(ArithLogOper oper, u64 arg_0, u64 arg_1);
	void exec_load_instr(LoadType load_type, u64 address);
	void exec_store_instr(StoreType store_type, u64 address, u64 data);
	void exec_syscall(SystemCall system_call);
};

}


#endif		// src__slash__vm_class_hpp
