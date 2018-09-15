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

public:		// enums
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

public:		// functions
	Vm(size_t s_mem_amount, const std::string& s_code_filename);
	virtual ~Vm();

	int run();

	gen_getter_by_val(mem_amount)
	gen_getter_by_con_ref(code_filename)
};

}


#endif		// src__slash__vm_class_hpp
