#include "vm_class.hpp"
#include <fstream>

namespace cakeplusplus
{

size_t Vm::InstrHeader::num_arg_bytes() const
{
	switch (group())
	{
		case 0:
			return 0;

		case 1:
			return 2;

		case 2:
			switch (oper())
			{
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Constu8):
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Consts8):
					return 1;

				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Constu16):
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Consts16):
					return 2;

				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Constu32):
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Consts32):
					return 4;

				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Const):
					return 8;

				default:
					return 0;
			}

		case 3:
		case 4:
			return 0;

		default:
			return 0;
	}
}

bool Vm::InstrHeader::arg_is_signed() const
{
	switch (group())
	{
		case 0:
			return false;

		case 1:
			return true;

		case 2:
			switch (oper())
			{
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Constu8):
					return false;
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Consts8):
					return true;

				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Constu16):
					return false;
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Consts16):
					return true;

				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Constu32):
					return false;
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Consts32):
					return true;

				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Const):
					return false;

				default:
					return 0;
			}

		case 3:
		case 4:
			return false;

		default:
			return false;
	}
}

bool Vm::InstrHeader::valid() const
{
	switch (group())
	{
		case 0:
			return (oper() < static_cast<decltype(oper())>
				(Vm::InstrGrp0Oper::Invalid));

		case 1:
			return (oper() < static_cast<decltype(oper())>
				(Vm::InstrGrp1Oper::Invalid));

		case 2:
			return (oper() < static_cast<decltype(oper())>
				(Vm::InstrGrp2Oper::Invalid));

		case 3:
			return (oper() < static_cast<decltype(oper())>
				(Vm::InstrGrp3Oper::Invalid));

		case 4:
			return (oper() < static_cast<decltype(oper())>
				(Vm::InstrGrp4Oper::Invalid));

		default:
			//printout("The worst of the eeks!\n");
			return false;
	}
}

Vm::Vm(size_t s_mem_amount, const std::string& s_code_filename)
	: __mem_amount(s_mem_amount), __code_filename(s_code_filename)
{
	__pc = 0;
	//__sp = 0;
	__fp = 0;

	if (mem_amount() > max_mem_amount)
	{
		err("Error:  Too much memory requested.  Max amount ",
			"permitted:  ", max_mem_amount);
	}

	__mem.reset(new u8[mem_amount()]);

	std::fstream code_file(code_filename(), (std::ios_base::in
		| std::ios_base::binary));

	size_t i = 0;
	do
	{
		if (i >= mem_amount())
		{
			err("Not enough memory requested for file \"",
				code_filename(), "\"!  Amount requested was ",
				mem_amount(), ".");
		}

		const int c = code_file.get();
		__mem[i] = c;
		//printout("debug:  ", std::hex, (size_t)__mem[i], std::dec, "\n");

		++i;
		++__sp;
		++__fp;

	} while (!code_file.eof());

	__sp += 16;
	__fp += 8;

	// Clear the rest of the allocated memory.
	for (; i<mem_amount(); ++i)
	{
		__mem[i] = 0;
	}


}

Vm::~Vm()
{
}

int Vm::run()
{
	for (;;)
	{
		const InstrHeader curr_instr_header(ld_instr_header_and_inc_pc());

		if (!curr_instr_header.valid())
		{
			err("Vm::run():  Invalid instruction!");
		}

		u64 extended_arg = 0;
		const bool encoded_arg_is_signed
			= curr_instr_header.arg_is_signed();

		switch (curr_instr_header.num_arg_bytes())
		{
			case 0:
				break;

			case 1:
				switch (encoded_arg_is_signed)
				{
					case false:
						extended_arg = ldu8_extended_and_inc_pc();
						break;

					case true:
						extended_arg = lds8_extended_and_inc_pc();
						break;
				}
				break;

			case 2:
				switch (encoded_arg_is_signed)
				{
					case false:
						extended_arg = ldu16_extended_and_inc_pc();
						break;

					case true:
						extended_arg = lds16_extended_and_inc_pc();
						break;
				}
				break;

			case 4:
				switch (encoded_arg_is_signed)
				{
					case false:
						extended_arg = ldu32_extended_and_inc_pc();
						break;

					case true:
						extended_arg = lds32_extended_and_inc_pc();
						break;
				}
				break;

			case 8:
				extended_arg = ld64_and_inc_pc();
				break;

			default:
				err("Vm::run():  ",
					"switch (curr_instr_header.num_arg_bytes()):  ",
					"Eek!");
				break;
		}

		//printout("stuffs:  ", std::hex, __pc, ", ", 
		//	extended_arg, std::dec, "\n");
		//printout("more stuffs:  ", std::hex, __pc, ", ",
		//	(size_t)curr_instr_header.group(), ", ",
		//	(size_t)curr_instr_header.oper(), std::dec, "\n");

		switch (curr_instr_header.group())
		{
			case 0:
				handle_instr_from_group_0(curr_instr_header.oper(),
					extended_arg);
				break;
			case 1:
				handle_instr_from_group_1(curr_instr_header.oper(),
					extended_arg);
				break;
			case 2:
				handle_instr_from_group_2(curr_instr_header.oper(),
					extended_arg);
				break;
			case 3:
				handle_instr_from_group_3(curr_instr_header.oper(),
					extended_arg);
				break;
			case 4:
				handle_instr_from_group_4(curr_instr_header.oper(),
					extended_arg);
				break;
		}
	}

	return 0;
}

u8 Vm::get_raw_mem8_at(Address where) const
{
	if (where < mem_amount())
	{
		return __mem[where];
	}
	else // if (where >= mem_amount)
	{
		err("Error:  get_raw_mem8_at():  address 0x", std::hex, where,
			std::dec, " not in allocated memory range!");

		return get_bits_with_range(9001, 7, 0);
	}
}
u16 Vm::get_raw_mem16_at(Address where) const
{
	u16 ret = 0;
	set_bits_with_range(ret, get_raw_mem8_at(where + 0), 15, 8);
	set_bits_with_range(ret, get_raw_mem8_at(where + 1), 7, 0);

	//printout("get_raw_mem16_at():  ", std::hex, where, ", ", ret, std::dec,
	//	"\n");
	return ret;
}
u32 Vm::get_raw_mem32_at(Address where) const
{
	u32 ret = 0;
	set_bits_with_range(ret, get_raw_mem8_at(where + 0), 31, 24);
	set_bits_with_range(ret, get_raw_mem8_at(where + 1), 23, 16);
	set_bits_with_range(ret, get_raw_mem8_at(where + 2), 15, 8);
	set_bits_with_range(ret, get_raw_mem8_at(where + 3), 7, 0);
	return ret;
}
u64 Vm::get_mem64_at(Address where) const
{
	u64 ret = 0;
	set_bits_with_range(ret, get_raw_mem8_at(where + 0), 63, 56);
	set_bits_with_range(ret, get_raw_mem8_at(where + 1), 55, 48);
	set_bits_with_range(ret, get_raw_mem8_at(where + 2), 47, 40);
	set_bits_with_range(ret, get_raw_mem8_at(where + 3), 39, 32);
	set_bits_with_range(ret, get_raw_mem8_at(where + 4), 31, 24);
	set_bits_with_range(ret, get_raw_mem8_at(where + 5), 23, 16);
	set_bits_with_range(ret, get_raw_mem8_at(where + 6), 15, 8);
	set_bits_with_range(ret, get_raw_mem8_at(where + 7), 7, 0);
	return ret;
}

void Vm::set_mem8_at(Address where, u8 data)
{
	if (where < mem_amount())
	{
		__mem[where] = data;
	}
	else // if (where >= mem_amount)
	{
		err("Error:  set_mem8_at():  address 0x", std::hex, where,
			std::dec, " not in allocated memory range!");
	}
}
void Vm::set_mem16_at(Address where, u16 data)
{
	set_mem8_at(where + 0, data >> 8);
	set_mem8_at(where + 1, data >> 0);
}
void Vm::set_mem32_at(Address where, u32 data)
{
	set_mem8_at(where + 0, data >> 24);
	set_mem8_at(where + 1, data >> 16);
	set_mem8_at(where + 2, data >> 8);
	set_mem8_at(where + 3, data >> 0);
}
void Vm::set_mem64_at(Address where, u64 data)
{
	set_mem8_at(where + 0, data >> 56);
	set_mem8_at(where + 1, data >> 48);
	set_mem8_at(where + 2, data >> 40);
	set_mem8_at(where + 3, data >> 32);
	set_mem8_at(where + 4, data >> 24);
	set_mem8_at(where + 5, data >> 16);
	set_mem8_at(where + 6, data >> 8);
	set_mem8_at(where + 7, data >> 0);
}

void Vm::handle_instr_from_group_0(u8 oper, u64 extended_arg)
{
	const ArithLogOper arith_log_oper = static_cast<ArithLogOper>(oper);
	const LoadType load_type = static_cast<LoadType>(oper
		- static_cast<decltype(oper)>(InstrGrp0Oper::Ldux8));
	const StoreType store_type = static_cast<StoreType>(oper
		- static_cast<decltype(oper)>(InstrGrp0Oper::Stx8));

	switch (oper)
	{
		case static_cast<u8>(InstrGrp0Oper::Add):
		case static_cast<u8>(InstrGrp0Oper::Sub):
		case static_cast<u8>(InstrGrp0Oper::Mul):
		case static_cast<u8>(InstrGrp0Oper::Udiv):
		case static_cast<u8>(InstrGrp0Oper::Sdiv):
		case static_cast<u8>(InstrGrp0Oper::Umod):
		case static_cast<u8>(InstrGrp0Oper::Smod):
		case static_cast<u8>(InstrGrp0Oper::Uslt):
		case static_cast<u8>(InstrGrp0Oper::Sslt):
		case static_cast<u8>(InstrGrp0Oper::And):
		case static_cast<u8>(InstrGrp0Oper::Or):
		case static_cast<u8>(InstrGrp0Oper::Xor):
		case static_cast<u8>(InstrGrp0Oper::Lsl):
		case static_cast<u8>(InstrGrp0Oper::Lsr):
		case static_cast<u8>(InstrGrp0Oper::Asr):
			{
				const auto temp_0 = pop();
				const auto temp_1 = pop();
				exec_arithlog_instr(arith_log_oper, temp_0, temp_1);
			}
			break;

		case static_cast<u8>(InstrGrp0Oper::Ldux8):
		case static_cast<u8>(InstrGrp0Oper::Ldsx8):
		case static_cast<u8>(InstrGrp0Oper::Ldux16):
		case static_cast<u8>(InstrGrp0Oper::Ldsx16):
		case static_cast<u8>(InstrGrp0Oper::Ldux32):
		case static_cast<u8>(InstrGrp0Oper::Ldsx32):
		case static_cast<u8>(InstrGrp0Oper::Ldx64):
			{
				const auto temp_0 = pop();
				const auto temp_1 = pop();
				exec_load_instr(load_type, (temp_0 + temp_1));
			}
			break;

		case static_cast<u8>(InstrGrp0Oper::Stx8):
		case static_cast<u8>(InstrGrp0Oper::Stx16):
		case static_cast<u8>(InstrGrp0Oper::Stx32):
		case static_cast<u8>(InstrGrp0Oper::Stx64):
			{
				const auto temp_0 = pop();
				const auto temp_1 = pop();
				const auto temp_2 = pop();
				exec_store_instr(store_type, (temp_0 + temp_1), temp_2);
			}
			break;

		case static_cast<u8>(InstrGrp0Oper::Jmpx):
			{
				const auto temp_0 = pop();
				const auto temp_1 = pop();
				__pc = temp_0 + temp_1;
			}
			break;
		case static_cast<u8>(InstrGrp0Oper::Jfal):
			{
				const auto cond = pop();
				const auto temp = pop();
				if (cond == 0)
				{
					__pc = temp;
				}
			}
			break;
		case static_cast<u8>(InstrGrp0Oper::Jtru):
			{
				const auto cond = pop();
				const auto temp = pop();
				if (cond != 0)
				{
					__pc = temp;
				}
			}
			break;
		default:
			err("Vm::handle_instr_from_group_0():  Eek!");
			break;
	}
}
void Vm::handle_instr_from_group_1(u8 oper, u64 extended_arg)
{
	const ArithLogOper arith_log_oper = static_cast<ArithLogOper>(oper);
	const LoadType load_type = static_cast<LoadType>(oper
		- static_cast<decltype(oper)>(InstrGrp1Oper::Ldux8i));
	const StoreType store_type = static_cast<StoreType>(oper
		- static_cast<decltype(oper)>(InstrGrp1Oper::Stx8i));

	switch (oper)
	{
		case static_cast<u8>(InstrGrp1Oper::Addi):
		case static_cast<u8>(InstrGrp1Oper::Subi):
		case static_cast<u8>(InstrGrp1Oper::Muli):
		case static_cast<u8>(InstrGrp1Oper::Udivi):
		case static_cast<u8>(InstrGrp1Oper::Sdivi):
		case static_cast<u8>(InstrGrp1Oper::Umodi):
		case static_cast<u8>(InstrGrp1Oper::Smodi):
		case static_cast<u8>(InstrGrp1Oper::Uslti):
		case static_cast<u8>(InstrGrp1Oper::Sslti):
		case static_cast<u8>(InstrGrp1Oper::Andi):
		case static_cast<u8>(InstrGrp1Oper::Ori):
		case static_cast<u8>(InstrGrp1Oper::Xori):
		case static_cast<u8>(InstrGrp1Oper::Lsli):
		case static_cast<u8>(InstrGrp1Oper::Lsri):
		case static_cast<u8>(InstrGrp1Oper::Asri):
			exec_arithlog_instr(arith_log_oper, pop(), extended_arg);
			break;

		case static_cast<u8>(InstrGrp1Oper::Ldux8i):
		case static_cast<u8>(InstrGrp1Oper::Ldsx8i):
		case static_cast<u8>(InstrGrp1Oper::Ldux16i):
		case static_cast<u8>(InstrGrp1Oper::Ldsx16i):
		case static_cast<u8>(InstrGrp1Oper::Ldux32i):
		case static_cast<u8>(InstrGrp1Oper::Ldsx32i):
		case static_cast<u8>(InstrGrp1Oper::Ldx64i):
			exec_load_instr(load_type, (pop() + extended_arg));
			break;

		case static_cast<u8>(InstrGrp1Oper::Stx8i):
		case static_cast<u8>(InstrGrp1Oper::Stx16i):
		case static_cast<u8>(InstrGrp1Oper::Stx32i):
		case static_cast<u8>(InstrGrp1Oper::Stx64i):
			{
				const Address address = pop() + extended_arg;
				const auto data = pop();
				exec_store_instr(store_type, address, data);
			}
			break;

		case static_cast<u8>(InstrGrp1Oper::Jmpxi):
			__pc = pop() + pop();
			break;
		case static_cast<u8>(InstrGrp1Oper::Bfal):
			{
				const auto cond = pop();
				const auto temp = extended_arg;
				if (cond == 0)
				{
					__pc += temp;
				}
			}
			break;
		case static_cast<u8>(InstrGrp1Oper::Btru):
			{
				const auto cond = pop();
				const auto temp = extended_arg;
				if (cond != 0)
				{
					__pc += temp;
				}
			}
			break;
		default:
			err("Vm::handle_instr_from_group_1():  Eek!");
			break;
	}
}
void Vm::handle_instr_from_group_2(u8 oper, u64 extended_arg)
{
	switch (oper)
	{
		case static_cast<u8>(InstrGrp2Oper::Constu8):
		case static_cast<u8>(InstrGrp2Oper::Consts8):
		case static_cast<u8>(InstrGrp2Oper::Constu16):
		case static_cast<u8>(InstrGrp2Oper::Consts16):
		case static_cast<u8>(InstrGrp2Oper::Constu32):
		case static_cast<u8>(InstrGrp2Oper::Consts32):
		case static_cast<u8>(InstrGrp2Oper::Const):
			// Well, that was easy.
			push(extended_arg);
			break;

		default:
			err("Vm::handle_instr_from_group_2():  Eek!");
			break;
	}
}
void Vm::handle_instr_from_group_3(u8 oper, u64 extended_arg)
{
	switch (oper)
	{
		case static_cast<u8>(InstrGrp3Oper::Arg):
			push(__fp - 8);
			break;
		case static_cast<u8>(InstrGrp3Oper::Var):
			push(__fp + 16);
			break;
		case static_cast<u8>(InstrGrp3Oper::GetPc):
			push(__pc);
			break;

		default:
			err("Vm::handle_instr_from_group_3():  Eek!");
			break;
	}
}
void Vm::handle_instr_from_group_4(u8 oper, u64 extended_arg)
{
	switch (oper)
	{
		case static_cast<u8>(InstrGrp4Oper::Argx):
			push(__fp - 8 + pop());
			break;
		case static_cast<u8>(InstrGrp4Oper::Varx):
			push(__fp + 16 + pop());
			break;
		case static_cast<u8>(InstrGrp4Oper::AddToSp):
			__sp += pop();
			break;
		case static_cast<u8>(InstrGrp4Oper::Call):
			{
				const auto old_fp = __fp;
				const auto addr = pop();
				__fp = __sp;
				push(__pc);
				push(old_fp);
				__pc = addr;
			}
			break;
		case static_cast<u8>(InstrGrp4Oper::Ret):
			{
				const auto ret_addr = get_mem64_at(__fp);
				const auto old_fp = get_mem64_at(__fp + 8);
				__sp = __fp;
				__fp = old_fp;
				__pc = ret_addr;
			}
			break;

		case static_cast<u8>(InstrGrp4Oper::Syscall):
			exec_syscall(static_cast<SystemCall>(pop()));
			break;

		default:
			err("Vm::handle_instr_from_group_3():  Eek!");
			break;
	}
}

void Vm::exec_arithlog_instr(ArithLogOper oper, u64 arg_0, u64 arg_1)
{
	switch (oper)
	{
		case ArithLogOper::Add:
			push(arg_0 + arg_1);
			break;
		case ArithLogOper::Sub:
			push(arg_0 - arg_1);
			break;
		case ArithLogOper::Mul:
			push(arg_0 * arg_1);
			break;
		case ArithLogOper::Udiv:
			push(arg_0 / arg_1);
			break;
		case ArithLogOper::Sdiv:
			push(static_cast<s64>(arg_0) / static_cast<s64>(arg_1));
			break;
		case ArithLogOper::Umod:
			push(arg_0 % arg_1);
			break;
		case ArithLogOper::Smod:
			push(static_cast<s64>(arg_0) % static_cast<s64>(arg_1));
			break;
		case ArithLogOper::Uslt:
			push(arg_0 < arg_1);
			break;
		case ArithLogOper::Sslt:
			push(static_cast<s64>(arg_0) < static_cast<s64>(arg_1));
			break;
		case ArithLogOper::And:
			push(arg_0 & arg_1);
			break;
		case ArithLogOper::Or:
			push(arg_0 | arg_1);
			break;
		case ArithLogOper::Xor:
			push(arg_0 ^ arg_1);
			break;
		case ArithLogOper::Lsl:
			push(arg_0 << arg_1);
			break;
		case ArithLogOper::Lsr:
			push(arg_0 >> arg_1);
			break;
		case ArithLogOper::Asr:
			push(static_cast<s64>(arg_0) >> arg_1);
			break;

		default:
			err("Vm::exec_arithlog_instr():  Eek!");
	}
}
void Vm::exec_load_instr(LoadType load_type, u64 address)
{
	switch (load_type)
	{
		case LoadType::U8:
			push(get_extended_mem_u8_at(address));
			break;
		case LoadType::S8:
			push(get_extended_mem_s8_at(address));
			break;

		case LoadType::U16:
			push(get_extended_mem_u16_at(address));
			break;
		case LoadType::S16:
			push(get_extended_mem_s16_at(address));
			break;

		case LoadType::U32:
			push(get_extended_mem_u32_at(address));
			break;
		case LoadType::S32:
			push(get_extended_mem_s32_at(address));
			break;

		case LoadType::Any64:
			push(get_mem64_at(address));
			break;

		default:
			err("Vm::exec_load_instr():  Eek!");
			break;
	}
}

void Vm::exec_store_instr(StoreType store_type, u64 address, u64 data)
{
	switch (store_type)
	{
		case StoreType::Any8:
			set_mem8_at(address, get_bits_with_range(data, 7, 0));
			break;

		case StoreType::Any16:
			set_mem16_at(address, get_bits_with_range(data, 15, 0));
			break;

		case StoreType::Any32:
			set_mem32_at(address, get_bits_with_range(data, 31, 0));
			break;

		case StoreType::Any64:
			set_mem64_at(address, data);
			break;

		default:
			err("Vm::exec_store_instr():  Eek!");
			break;
	}
}

void Vm::exec_syscall(SystemCall system_call)
{
	switch (system_call)
	{
		case SystemCall::DispChar:
			printout(static_cast<char>(pop()));
			break;

		case SystemCall::DispStr:
			{
				Address address = pop();
				std::string to_print;

				char c = 1;
				while (c != '\0')
				{
					c = get_raw_mem8_at(address);
					++address;

					if (c != '\0')
					{
						to_print += c;
					}
				}

				printout(to_print);
			}
			break;

		case SystemCall::DispUInt:
			printout(static_cast<u64>(pop()));
			break;

		case SystemCall::DispSInt:
			printout(static_cast<s64>(pop()));
			break;

		case SystemCall::Exit:
			exit(pop());
			break;
	}
}

}
